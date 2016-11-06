#include <std_c++.h>
#include <CNascom/CNascom.h>
#include <CArgs/CArgs.h>
#include <CXLib/CXMachine.h>
#include <CXLib/CXWindow.h>
#include <CXLib/CXImage.h>
#include <CXLibPixelRenderer/CXLibPixelRenderer.h>
#include <CAtExit/CAtExit.h>
#include <COS/COS.h>

struct CNascomXScreen : public CZ80Screen {
  typedef map<uchar,CImagePtr> CharImageMap;

  CNascom            &nascom;
  CXLibPixelRenderer *renderer;
  int                 border;

  CNascomXScreen(CNascom &nascom1, CXLibPixelRenderer *renderer1) :
   CZ80Screen(*nascom1.getZ80()), nascom(nascom1), renderer(renderer1), border(0) {
    border = 4*nascom.getScale();
  }

  virtual ~CNascomXScreen() { }

  void memChanged(ushort pos, ushort len);

  void redraw();
};

struct CNascomEventAdapter : public CXEventAdapter {
  CNascomXScreen *screen;
  CZ80           *z80;

  CNascomEventAdapter(CNascomXScreen *screen1, CZ80 *z801) :
   CXEventAdapter(KeyPress | KeyRelease | Expose),
   screen(screen1), z80(z801) {
  }

  bool keyPressEvent  (const CKeyEvent &kevent);
  bool keyReleaseEvent(const CKeyEvent &kevent);

  bool exposeEvent();

  bool idleEvent();
};

struct CNascomXAtExit : public CAtExit {
  CNascom *nascom;

  CNascomXAtExit(CNascom *nascom1) :
   nascom(nascom1) {
  }

  void operator()() {
    nascom->getZ80()->dumpOpCounts(cout);
  }
};

class CNascomXRenderer : public CNascomRenderer {
 public:
  CNascomXRenderer(CPixelRenderer *renderer) :
   renderer_(renderer) {
  }

  void clear(const CRGBA &bg);

  void drawImage(const CIPoint2D &p, CImagePtr image);

 private:
  CPixelRenderer *renderer_;
};

int
main(int argc, char **argv)
{
  CNascom nascom;

  CArgs cargs("-v:f        (verbose) "
              "-dump:f     (enable dump) "
              "-bin:f      (input file is binary) "
              "-snapshot:f (input file is snapshot) "
              "-icount:f   (output instruction counts on exit) "
              "-invert:f   (invert screen colors) "
              "-scale:i=1  (scale factor) "
              "-chars:s    (file containg charset image - 128x256 xpm) "
              );

  cargs.parse(&argc, argv);

  bool   v_flag        = cargs.getBooleanArg("-v");
  bool   dump_flag     = cargs.getBooleanArg("-dump");
  bool   bin_flag      = cargs.getBooleanArg("-bin");
  bool   snapshot_flag = cargs.getBooleanArg("-snapshot");
  bool   icount        = cargs.getBooleanArg("-icount");
  bool   invert        = cargs.getBooleanArg("-invert");
  int    scale         = cargs.getIntegerArg("-scale");
  string chars         = cargs.getStringArg ("-chars");

  CZ80 *z80 = nascom.getZ80();

  z80->setVerbose(v_flag);
  z80->setDump(dump_flag);

  nascom.setInvert(invert);
  nascom.setScale (scale );

  //------

  int border = 4*scale;

  CXWindow *xwindow =
    new CXWindow(scale*nascom.getScreenPixelWidth () + 2*border,
                 scale*nascom.getScreenPixelHeight() + 2*border);

  xwindow->setWindowTitle("Nascom II Emulator");

  xwindow->selectKeyInput ();
  xwindow->selectExposures();

  CXLibPixelRenderer *renderer = new CXLibPixelRenderer(xwindow);

  //------

  CNascomXScreen *screen = new CNascomXScreen(nascom, renderer);

  z80->setScreen(screen);

  //------

  xwindow->map();

  //------

  for (int i = 1; i < argc; ++i) {
    if      (bin_flag)
      z80->loadBin(argv[i]);
    else if (snapshot_flag)
      z80->loadSnapshot(argv[i]);
    else
      z80->load(argv[i]);
  }

  if (! snapshot_flag)
    z80->setPC(0);

  if (icount)
    new CNascomXAtExit(&nascom);

  if (chars != "")
    nascom.loadChars(chars);

  CNascomEventAdapter *adapter = new CNascomEventAdapter(screen, z80);

  CXMachineInst->setEventAdapter(adapter);

  CXMachineInst->mainLoop();
}

void
CNascomXScreen::
memChanged(ushort, ushort)
{
#if 0
  renderer->startDoubleBuffer();

  int x, y;

  ushort pos1 = pos;
  ushort pos2 = pos + len - 1;

  for (ushort pos = pos1; pos <= pos2; ++pos)
    if (nascom.getScreenPos(pos, &x, &y)) {
      uchar c = z80.getByte(pos);

      int px = scale*nascom.getCharWidth ()*x + border;
      int py = scale*nascom.getCharHeight()*y + border;

      renderer->drawImage(px, py, getCharImage(c));
    }

  renderer->endDoubleBuffer();
#endif

  redraw();
}

void
CNascomXScreen::
redraw()
{
  renderer->startDoubleBuffer();

  CNascomXRenderer nrenderer(renderer);

  nascom.draw(&nrenderer, border);

  renderer->endDoubleBuffer();
}

bool
CNascomEventAdapter::
keyPressEvent(const CKeyEvent &kevent)
{
  CKeyType type = kevent.getType();

  if      (type == CKEY_TYPE_Escape)
    exit(0);
  else if (type == CKEY_TYPE_F1)
    z80->saveSnapshot();
  else if (type == CKEY_TYPE_F2)
    z80->resetOpCounts();
  else
    z80->keyPress(kevent);

  return true;
}

bool
CNascomEventAdapter::
keyReleaseEvent(const CKeyEvent &kevent)
{
  CKeyType type = kevent.getType();

  if (type == CKEY_TYPE_Escape || type == CKEY_TYPE_F1 || type == CKEY_TYPE_F2)
    return false;

  z80->keyRelease(kevent);

  return true;
}

bool
CNascomEventAdapter::
exposeEvent()
{
  screen->redraw();

  return true;
}

bool
CNascomEventAdapter::
idleEvent()
{
  z80->step();

  return true;
}

void
CNascomXRenderer::
clear(const CRGBA &bg)
{
  renderer_->setBackground(bg);

  renderer_->clear();
}

void
CNascomXRenderer::
drawImage(const CIPoint2D &p, CImagePtr image)
{
  renderer_->drawImage(p, image);
}

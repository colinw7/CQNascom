#include "std_c++.h"
#include "CNascom/CNascom.h"
#include "CArgs/CArgs.h"
#include "CWinLib/CWinMachine.h"
#include "CWinLib/CWinWindow.h"
#include "CWinLib/CWinImage.h"
#include "CUtil/CAtExit.h"
#include "COS/COS.h"

struct CNascomWinScreen : public CZ80Screen {
  CNascom    &nascom;
  CWinWindow *window;
  int         scale;
  int         border;

  CNascomWinScreen(CNascom &nascom1, int scale1, bool invert) :
   CZ80Screen(*nascom1.getZ80()), nascom(nascom1),
   scale(scale1), border(4*scale) {
    nascom.setInvert(invert);
    nascom.setScale (scale);

    window = new CWinWindow(scale*nascom.getScreenPixelWidth () + 2*border,
                            scale*nascom.getScreenPixelHeight() + 2*border);

    window->setTitle("Nascom II Emulator");

    if (! invert)
      window->setBackground(CRGB(0,0,0));
    else
      window->setBackground(CRGB(1,1,1));

    window->map();
  }

  virtual ~CNascomWinScreen() {
    delete window;
  }

  void memChanged(unsigned short pos, unsigned short len);

  void redraw();
};

struct CNascomEventAdapter : public CWinMachineEventAdapter {
  CNascomWinScreen *screen;
  CZ80             *z80;

  CNascomEventAdapter(CNascomWinScreen *screen1, CZ80 *z801) :
    CWinMachineEventAdapter(),
    screen(screen1), z80(z801) {
  }

  void keyPress  ();
  void keyRelease();

  void expose();

  void idle();
};

struct CNascomWinAtExit : public CAtExit {
  CNascom *nascom;

  CNascomWinAtExit(CNascom *nascom1) :
   nascom(nascom1) {
  }

  void operator()() {
    nascom->getZ80()->dumpOpCounts(cout);
  }
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

  CNascomWinScreen *screen = new CNascomWinScreen(nascom, scale, invert);

  z80->setScreen(screen);

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
    new CNascomWinAtExit(&nascom);

  if (chars != "")
    nascom.loadChars(chars);

  CNascomEventAdapter *adapter = new CNascomEventAdapter(screen, z80);

  CWinMachineInst->setEventAdapter(adapter);

  CWinMachineInst->mainLoop();
}

void
CNascomWinScreen::
memChanged(unsigned short pos, unsigned short len)
{
  int x, y;

  unsigned short pos1 = pos;
  unsigned short pos2 = pos + len - 1;

  for (unsigned short pos = pos1; pos <= pos2; ++pos)
    if (nascom.getScreenPos(pos, &x, &y)) {
      unsigned char c = z80.getByte(pos);

      int px = scale*nascom.getCharWidth ()*x + border;
      int py = scale*nascom.getCharHeight()*y + border;

      window->drawImage(nascom.getCharImage(c), px, py);
    }
}

void
CNascomWinScreen::
redraw()
{
  window->startDoubleBuffer();

  window->clear();

  unsigned short y = border;

  for (unsigned short j = 0; j < nascom.getScreenCharHeight(); ++j) {
    unsigned short pos = nascom.getScreenMemLineStart(j);

    unsigned short x = border;

    for (unsigned short i = 0; i < nascom.getScreenCharWidth(); ++i, ++pos) {
      unsigned char c = z80.getByte(pos);

      window->drawImage(nascom.getCharImage(c), x, y);

      x += scale*nascom.getCharWidth();
    }

    y += scale*nascom.getCharHeight();
  }

  window->endDoubleBuffer();
}

void
CNascomEventAdapter::
keyPress()
{
}

void
CNascomEventAdapter::
keyRelease()
{
}

void
CNascomEventAdapter::
expose()
{
  screen->redraw();
}

void
CNascomEventAdapter::
idle()
{
  z80->step();
}

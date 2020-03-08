#include <CQNascom.h>
#include <CNascom.h>
#include <CQZ80Dbg.h>

#include <CArgs.h>
#include <CQApp.h>
#include <CQImageUtil.h>
#include <CQUtil.h>

#include <QWidget>
#include <QPainter>
#include <QTimer>

int
main(int argc, char **argv)
{
  CQApp app(argc, argv);

  CArgs cargs("-v:f        (verbose) "
              "-dump:f     (enable dump) "
              "-bin:f      (input file is binary) "
              "-snapshot:f (input file is snapshot) "
              "-icount:f   (output instruction counts on exit) "
              "-invert:f   (invert screen colors) "
              "-scale:i=1  (scale factor) "
              "-debug:f    (debug) "
              "-chars:s    (file containg charset image - 128x256 xpm) "
              );

  cargs.parse(&argc, argv);

  bool        verbose  = cargs.getBooleanArg("-v");
  bool        dump     = cargs.getBooleanArg("-dump");
  bool        bin      = cargs.getBooleanArg("-bin");
  bool        snapshot = cargs.getBooleanArg("-snapshot");
//bool        icount   = cargs.getBooleanArg("-icount");
  bool        invert   = cargs.getBooleanArg("-invert");
  int         scale    = cargs.getIntegerArg("-scale");
  bool        debug    = cargs.getBooleanArg("-debug");
  std::string chars    = cargs.getStringArg ("-chars");

  CNascom *nascom = new CNascom;

  CZ80 *z80 = nascom->getZ80();

  z80->setVerbose(verbose);
  z80->setDump(dump);

  nascom->setInvert(invert);
  nascom->setScale (scale );

  //------

  int border = 4*scale;

  int w = scale*nascom->getScreenPixelWidth () + 2*border;
  int h = scale*nascom->getScreenPixelHeight() + 2*border;

  CQNascom *qnascom = new CQNascom(nascom, w, h);

  //qnascom->setWindowTitle("Nascom II Emulator");

  z80->setScreen(qnascom);

  //------

  for (int i = 1; i < argc; ++i) {
    if      (bin)
      z80->loadBin(argv[i]);
    else if (snapshot)
      z80->loadSnapshot(argv[i]);
    else
      z80->load(argv[i]);
  }

  if (! snapshot)
    z80->setPC(0);

  if (chars != "")
    nascom->loadChars(chars);

  qnascom->show();

  //------

  if (debug)
    qnascom->addDebug();

  //------

  if (! debug)
    qnascom->exec();

  return app.exec();
}

//------

CQNascom::
CQNascom(CNascom *nascom, int w, int h) :
 CZ80Screen(*nascom->getZ80()), nascom_(nascom), border_(0)
{
  setFocusPolicy(Qt::StrongFocus);

  border_ = 4*nascom->getScale();

  resize(w, h);
}

CQNascom::
~CQNascom()
{
}

void
CQNascom::
exec()
{
  timer_ = new QTimer;

  connect(timer_, SIGNAL(timeout()), this, SLOT(timeOut()));

  timer_->start(1);
}

CQZ80Dbg *
CQNascom::
addDebug()
{
  if (! dbg_) {
    dbg_ = new CQZ80Dbg(nascom_->getZ80());

    dbg_->init();

    QFont fixedFont("Courier New", 16);

    dbg_->setFixedFont(fixedFont);
  }

  dbg_->show();
  dbg_->raise();

  return dbg_;
}

void
CQNascom::
screenMemChanged(ushort start, ushort len)
{
#if 0
  renderer->startDoubleBuffer();

  int x, y;

  ushort pos1 = pos;
  ushort pos2 = pos + len - 1;

  for (ushort pos = pos1; pos <= pos2; ++pos)
    if (nascom->getScreenPos(pos, &x, &y)) {
      uchar c = z80.getByte(pos);

      int px = scale*nascom->getCharWidth ()*x + border;
      int py = scale*nascom->getCharHeight()*y + border;

      renderer->drawImage(px, py, getCharImage(c));
    }

  renderer->endDoubleBuffer();
#endif

  if (nascom_->onScreen(start, len))
    update();
}

void
CQNascom::
redraw()
{
  update();
}

void
CQNascom::
paintEvent(QPaintEvent *)
{
  //renderer->startDoubleBuffer();

  QPainter painter(this);

  CQNascomRenderer nrenderer(this, &painter);

  nascom_->draw(&nrenderer, border_);

  //renderer->endDoubleBuffer();
}

void
CQNascom::
keyPressEvent(QKeyEvent *e)
{
  CKeyEvent *kevent = CQUtil::convertEvent(e);

  CKeyType type = kevent->getType();

  CZ80 *z80 = nascom_->getZ80();

  if      (type == CKEY_TYPE_Escape)
    exit(0);
  else if (type == CKEY_TYPE_F1)
    z80->saveSnapshot();
  else if (type == CKEY_TYPE_F2)
    z80->resetOpCounts();
  else
    z80->keyPress(*kevent);
}

void
CQNascom::
keyReleaseEvent(QKeyEvent *e)
{
  CKeyEvent *kevent = CQUtil::convertEvent(e);

  CKeyType type = kevent->getType();

  if (type == CKEY_TYPE_Escape || type == CKEY_TYPE_F1 || type == CKEY_TYPE_F2)
    return;

  CZ80 *z80 = nascom_->getZ80();

  z80->keyRelease(*kevent);
}

void
CQNascom::
timeOut()
{
  doSteps();
}

void
CQNascom::
doSteps()
{
  CZ80 *z80 = nascom_->getZ80();

  for (uint i = 0; i < 1000; ++i)
    z80->step();
}

//------------

void
CQNascomRenderer::
clear(const CRGBA &bg)
{
  painter_->fillRect(qnascom_->rect(), QBrush(CQUtil::rgbaToColor(bg)));
}

void
CQNascomRenderer::
drawImage(int x, int y, CImagePtr image)
{
  painter_->drawImage(x, y, CQImageUtil::toQImage(image));
}

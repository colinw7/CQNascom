#include "CQNascom.h"
#include "CQUtil.h"

#include <CNascom.h>
#include <CNascomChars.h>

#include <CKeyType.h>
#include <CArgs.h>

#include <QApplication>
#include <QKeyEvent>
#include <QWidget>
#include <QPainter>
#include <QTimer>

using std::string;

int
main(int argc, char **argv)
{
  QApplication app(argc, argv);

  CNascom *nascom = new CNascom;

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
//bool   icount        = cargs.getBooleanArg("-icount");
  bool   invert        = cargs.getBooleanArg("-invert");
  int    scale         = cargs.getIntegerArg("-scale");
  string chars         = cargs.getStringArg ("-chars");

  CZ80 *z80 = nascom->getZ80();

  z80->setVerbose(v_flag);
  z80->setDump(dump_flag);

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
    if      (bin_flag)
      z80->loadBin(argv[i]);
    else if (snapshot_flag)
      z80->loadSnapshot(argv[i]);
    else
      z80->load(argv[i]);
  }

  if (! snapshot_flag)
    z80->setPC(0);

  if (chars != "")
    qnascom->loadChars(chars);

  qnascom->show();

  return app.exec();
}

CQNascom::
CQNascom(CNascom *nascom, int w, int h) :
 CZ80Screen(*nascom->getZ80()), nascom_(nascom), border_(0)
{
  QTimer *timer = new QTimer;

  connect(timer, SIGNAL(timeout()), this, SLOT(timeOut()));

  setFocusPolicy(Qt::StrongFocus);

  border_ = 4*nascom->getScale();

  renderer_ = new CQNascomRenderer(this);

  resize(w, h);

  timer->start(1);
}

CQNascom::
~CQNascom()
{
  delete renderer_;
}

void
CQNascom::
loadChars(const string &filename)
{
  renderer_->loadChars(filename);
}

void
CQNascom::
memChanged(ushort start, ushort len)
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

      renderer->drawChar(px, py, c);
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

  renderer_->setPainter(&painter);

  nascom_->draw(renderer_, border_);

  //renderer->endDoubleBuffer();
}

void
CQNascom::
keyPressEvent(QKeyEvent *e)
{
  CKeyType type = CQUtil::convertKey(e->key(), e->modifiers());

  CZ80 *z80 = nascom_->getZ80();

  if      (type == CKEY_TYPE_Escape)
    exit(0);
  else if (type == CKEY_TYPE_F1)
    z80->saveSnapshot();
  else if (type == CKEY_TYPE_F2)
    z80->resetOpCounts();
  else
    z80->keyPress(type);
}

void
CQNascom::
keyReleaseEvent(QKeyEvent *e)
{
  CKeyType type = CQUtil::convertKey(e->key(), e->modifiers());

  if (type == CKEY_TYPE_Escape || type == CKEY_TYPE_F1 || type == CKEY_TYPE_F2)
    return;

  CZ80 *z80 = nascom_->getZ80();

  z80->keyRelease(type);
}

void
CQNascom::
timeOut()
{
  CZ80 *z80 = nascom_->getZ80();

  for (uint i = 0; i < 1000; ++i)
    z80->step();
}

//------------

CQNascomRenderer::
CQNascomRenderer(CQNascom *qnascom) :
 qnascom_(qnascom), painter_(0), chars_loaded_(false)
{
}

void
CQNascomRenderer::
setPainter(QPainter *painter)
{
  painter_ = painter;
}

void
CQNascomRenderer::
clear(bool invert)
{
  QColor c = (invert ? QColor(255,255,255) : QColor(0,0,0));

  painter_->fillRect(qnascom_->rect(), QBrush(c));
}

void
CQNascomRenderer::
drawChar(int x, int y, uchar c)
{
  painter_->drawImage(x, y, getCharImage(c));
}

QImage
CQNascomRenderer::
getCharImage(uchar c)
{
  if (! chars_loaded_)
    loadChars();

  return char_images_[c];
}

void
CQNascomRenderer::
loadChars()
{
  char_image_ = QImage(nascom_chars);

  loadImageChars();
}

void
CQNascomRenderer::
loadChars(const string &filename)
{
  char_image_ = QImage(filename.c_str());

  loadImageChars();
}

void
CQNascomRenderer::
loadImageChars()
{
  bool invert = qnascom_->getNascom()->getInvert();
  int  scale  = qnascom_->getNascom()->getScale ();

  int char_width  = 8;
  int char_height = 16;

  char_images_.resize(256);

  ushort y = 0;

  for (ushort j = 0, k = 0; j < 16; ++j) {
    ushort x = 0;

    for (ushort i = 0; i < 16; ++i, ++k) {
      QImage image1 = char_image_.copy(x, y, char_width, char_height);

      QImage image2;

      if (! invert) {
        image2 = invertPixels(image1);

        image1 = image2;
      }

      if (scale > 1) {
        QImage image2 = image1.scaled(scale*char_width, scale*char_height);

        image1 = image2;
      }

      char_images_[k] = image1;

      x += char_width;
    }

    y += char_height;
  }

  chars_loaded_ = true;
}

QImage
CQNascomRenderer::
invertPixels(QImage image)
{
  QImage image1;

  if (image.format() == QImage::Format_ARGB32 ||
      image.format() == QImage::Format_Indexed8)
    image1 = image;
  else
    image1 = image.convertToFormat(QImage::Format_ARGB32);

  int w = image1.width();
  int h = image1.height();

  QImage::Format format = image1.format();

  if (format == QImage::Format_ARGB32) {
    for (int y = 0; y < h; ++y) {
      for (int x = 0; x < w; ++x) {
        QRgb rgb = image1.pixel(x, y);

        int g = 255 - qGray(rgb);

        QRgb rgb1 = qRgba(g, g, g, 255);

        image1.setPixel(x, y, rgb1);
      }
    }
  }
  else {
    int ncolors = image1.colorCount();

    for (int i = 0; i < ncolors; ++i) {
      QRgb rgb = image1.color(i);

      int g = 255 - qGray(rgb);

      QRgb rgb1 = qRgba(g, g, g, 255);

      image1.setColor(i, rgb1);
    }
  }

  return image1;
}

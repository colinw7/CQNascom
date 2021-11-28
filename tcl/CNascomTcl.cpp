#include <std_c++.h>
#include <CNascom.h>
#include <CZ80TclLib.h>
#include <CZ80TclLibScreen.h>
#include <CXImage.h>
#include <CArgs.h>

struct CNascomScreen : public CZ80TclLibScreen {
  typedef std::map<uchar,CImagePtr> CharImageMap;

  CNascom      &nascom;
  CharImageMap  char_image_map;

  CNascomScreen(CNascom &nascom_1) :
   CZ80TclLibScreen(nascom_1.getScreenPixelWidth (),
                    nascom_1.getScreenPixelHeight(),
                    nascom_1.getScreenMemStart(),
                    nascom_1.getScreenMemEnd  ()),
   nascom(nascom_1) {
  }

  void redraw();

  bool containsMem(ushort pos, ushort len) {
    return nascom.onScreen(pos, len);
  }

  CImagePtr &getCharImage(uchar c);
};

int
main(int argc, char **argv)
{
  CNascom nascom;

  CArgs cargs("-v:f        (verbose) "
              "-debug:f    (enable debug) "
              "-dump:f     (enable dump) "
              "-bin:f      (input file is binary) "
              "-snapshot:f (input file is snapshot)"
              );

  cargs.parse(&argc, argv);

  bool v_flag        = cargs.getBooleanArg("-v");
  bool debug_flag    = cargs.getBooleanArg("-debug");
  bool dump_flag     = cargs.getBooleanArg("-dump");
  bool bin_flag      = cargs.getBooleanArg("-bin");
  bool snapshot_flag = cargs.getBooleanArg("-snapshot");

  CZ80 *z80 = nascom.getZ80();

  z80->setVerbose(v_flag);
  z80->setDump(dump_flag);

  CZ80TclLib app(argc, argv);

  app.init();

  app.setInitFileBin     (bin_flag);
  app.setInitFileSnapshot(snapshot_flag);

  app.setZ80(z80);

  if (! snapshot_flag)
    app.setStartup(0);

  app.setDebug(debug_flag);

  CNascomScreen *screen = new CNascomScreen(nascom);

  app.setScreen(screen);

  app.mainLoop();
}

void
CNascomScreen::
redraw()
{
  if (canvas == NULL)
    return;

  CZ80 *z80 = canvas->getZ80()->getZ80();

  canvas->clear();

  ushort y = 0;

  for (ushort j = 0; j < nascom.getScreenCharHeight(); ++j) {
    ushort pos = nascom.getScreenMemLineStart(j);

    ushort x = 0;

    for (ushort i = 0; i < nascom.getScreenCharWidth(); ++i, ++pos) {
      uchar c = z80->getByte(pos);

      canvas->drawImage(getCharImage(c), x, y);

      x += nascom.getCharWidth();
    }

    y += nascom.getCharHeight();
  }

  canvas->flush();
}

CImagePtr &
CNascomScreen::
getCharImage(uchar c)
{
  CharImageMap::iterator p = char_image_map.find(c);

  if (p != char_image_map.end())
    return p->second;

  char_image_map[c] = nascom.getCharImage(c);

  return char_image_map.find(c)->second;
}

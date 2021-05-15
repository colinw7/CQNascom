#ifndef CNASCOM_H
#define CNASCOM_H

#include <CZ80.h>
#include <CImagePtr.h>
#include <CRGBA.h>

class CNascomPortData;

class CNascomRenderer {
 public:
  CNascomRenderer() { }

  virtual ~CNascomRenderer() { }

  virtual void clear(const CRGBA &bg) = 0;

  virtual void drawImage(int x, int y, CImagePtr image) = 0;
};

class CNascom {
 public:
  CNascom();
 ~CNascom();

  void setInvert(bool invert) { invert_ = invert; }
  bool getInvert() { return invert_; }

  void setScale(int scale) { scale_ = scale; }
  int  getScale() const { return scale_; }

  CZ80 *getZ80() { return &z80_; }

  static uint getScreenPixelWidth ();
  static uint getScreenPixelHeight();

  static uint getScreenCharWidth () { return 48; }
  static uint getScreenCharHeight() { return 16; }

  static uint getCharWidth () { return 8; }
  static uint getCharHeight() { return 16; }

  static uint getScreenMemStart() { return 0x0800; }
  static uint getScreenMemEnd  () { return 0x0C00; }

  static uint getScreenMemLineStart(ushort line_num);

  bool onScreen(ushort pos, ushort len);

  bool getScreenPos(ushort pos, int *x, int *y);

  bool loadChars(const std::string &filename);

  CImagePtr getCharImage(uchar c);

  void draw(CNascomRenderer *renderer, int border=2);

 private:
  bool loadChars();

  bool loadChars(const CImagePtr &image);

 private:
  CZ80             z80_;
  CNascomPortData *port_data_    { nullptr };
  bool             invert_       { false };
  int              scale_        { 1 };
  bool             chars_loaded_ { false };
  CImagePtr        char_images_[256];
};

#endif

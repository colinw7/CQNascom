#include <CNascom.h>
#include <CStrUtil.h>

#include "CNascomKeyMap.h"
#include "CNascomScreenMap.h"
#include "roms/NASSYS3.h"
#include "roms/BASIC.h"

using std::string;
using std::cerr;
using std::endl;

class CNascomPortData : public CZ80PortData {
 public:
  CNascomPortData(CZ80 &z80) : CZ80PortData(z80) { }

  void out(uchar port, uchar value);

  uchar in(uchar port, uchar qual);

  void keyPress  (CKeyType key_type);
  void keyRelease(CKeyType key_type);

  bool lookupKey(CKeyType key_type, bool press, uint *row, uint *col, bool *shift);

  CKeyType keycodeToUpper(CKeyType key_type);
  char     keycodeToChar (CKeyType key_type);

 private:
  bool key_handled_;
};

static uchar key_state1[9];
static uchar key_state2[9];
static uint  key_pos;

static uchar serial_value = 0;
static bool  serial_ok    = false;

CNascom::
CNascom() :
 port_data_(NULL), invert_(false), scale_(1)
{
  z80_.setBytes(nassys3_memory, NASSYS3_MEM_START_POS,
                NASSYS3_MEM_END_POS - NASSYS3_MEM_START_POS + 1);

  z80_.setBytes(basic_memory, BASIC_MEM_START_POS,
                BASIC_MEM_END_POS - BASIC_MEM_START_POS + 1);

  port_data_ = new CNascomPortData(z80_);

  z80_.setPortData(port_data_);

  z80_.setMemFlags(0x0800, 1024, CZ80_MEM_SCREEN);
}

CNascom::
~CNascom()
{
  delete port_data_;
}

uint
CNascom::
getScreenPixelWidth()
{
  return getCharWidth ()*getScreenCharWidth ();
}

uint
CNascom::
getScreenPixelHeight()
{
  return getCharHeight()*getScreenCharHeight();
}

uint
CNascom::
getScreenMemLineStart(ushort line_num)
{
  return addr_map_l[line_num];
}

bool
CNascom::
onScreen(ushort pos, ushort len)
{
  ushort pos1 = pos;
  ushort pos2 = pos + len - 1;

  if (pos2 < addr_map_l[1] || pos1 > addr_map_r[0])
    return false;

  for (ushort i = 0; i < 16; ++i)
    if (pos2 >= addr_map_l[i] && pos1 <= addr_map_r[i])
      return true;

  return false;
}

bool
CNascom::
getScreenPos(ushort pos, int *x, int *y)
{
  if (pos < addr_map_l[1] || pos > addr_map_r[0])
    return false;

  for (ushort i = 0; i < 16; ++i)
    if (pos >= addr_map_l[i] && pos <= addr_map_r[i]) {
      *x = pos - addr_map_l[i];
      *y = i;
      return true;
    }

  return false;
}

#if 0
void *
CNascom::
getCharImage(uchar c)
{
  if (! chars_loaded_)
    chars_loaded_ = loadChars();

  return char_images_[c];
}

bool
CNascom::
loadChars()
{
  CImagePtr image = CImageMgrInst->createImage(src);

  image->readXPM((const char **) nascom_chars, sizeof(nascom_chars)/sizeof(char *));

  loadChars(image);

  chars_loaded_ = true;

  return true;
}

bool
CNascom::
loadChars(const string &filename)
{
  CFile file(filename);

  CImageFileSrc src(file);

  CImagePtr image = CImageMgrInst->createImage(src);

  loadChars(image);

  chars_loaded_ = true;

  return true;
}

bool
CNascom::
loadChars(const CImagePtr &image)
{
  ushort y = 0;

  for (ushort j = 0, k = 0; j < 16; ++j) {
    ushort x = 0;

    for (ushort i = 0; i < 16; ++i, ++k) {
      CImagePtr image1 = image->subImage(x, y, getCharWidth(), getCharHeight());

      if (! invert_)
        image1->invert();

      if (scale_ > 1) {
        CImagePtr image2 = image1->resize(scale_*getCharWidth(), scale_*getCharHeight());

        image1 = image2;
      }

      char_images_[k] = image1;

      x += getCharWidth();
    }

    y += getCharHeight();
  }

  return true;
}
#endif

void
CNascom::
draw(CNascomRenderer *renderer, int border)
{
  renderer->clear(invert_);

  ushort y = border;

  for (ushort j = 0; j < getScreenCharHeight(); ++j) {
    ushort pos = getScreenMemLineStart(j);

    ushort x = border;

    for (ushort i = 0; i < getScreenCharWidth(); ++i, ++pos) {
      uchar c = z80_.getByte(pos);

      renderer->drawChar(x, y, c);

      x += scale_*getCharWidth();
    }

    y += scale_*getCharHeight();
  }
}

//----------

void
CNascomPortData::
out(uchar port, uchar value)
{
  if      (port == 0) {
    static uchar value0;

    uchar down_trans = value0 & ~value;

    value0 = value;

    if (down_trans & 0x1) {
      if (key_pos < 8) ++key_pos;
    }

    if (down_trans & 0x2) {
      key_pos = 0;

      memcpy(key_state1, key_state2, sizeof(key_state2));
    }

    key_handled_ = true;
  }
  else if (port == 1) { // Serial Port
    cerr << "Serial Out: " << (int) value << endl;

    serial_value = value;
    serial_ok    = true;
  }
  else if (port == 2) // Serial Status
    cerr << "Serial Status: " << (int) value << endl;
  else
    cerr << "Out: Port " << (int) port << " Value " << (int) value << endl;
}

uchar
CNascomPortData::
in(uchar port, uchar)
{
  if      (port == 0) {
    uchar c = ~key_state1[key_pos];

    key_handled_ = true;

    return c;
  }
  else if (port == 1) // Serial Port
    return 0;
  else if (port == 2) { // Serial Status
    if (serial_ok) {
      serial_ok = false;

      return 0xFF;
    }
    else
      return 0;
  }

  return 0;
}

void
CNascomPortData::
keyPress(CKeyType key_type)
{
  uint row, col;
  bool shift;

  if (! lookupKey(key_type, true, &row, &col, &shift))
    return;

  SET_BIT(key_state2[row], col);

  if (shift)
    SET_BIT  (key_state2[0], 4);
  else
    RESET_BIT(key_state2[0], 4);

  key_handled_ = false;

  for (uint i = 0; i < 4000; ++i)
    z80.step();
}

void
CNascomPortData::
keyRelease(CKeyType key_type)
{
  uint row, col;
  bool shift;

  if (! lookupKey(key_type, false, &row, &col, &shift))
    return;

  RESET_BIT(key_state2[row], col);
  RESET_BIT(key_state2[0  ], 4  );

  key_handled_ = false;

  for (uint i = 0; i < 4000; ++i)
    z80.step();
}

bool
CNascomPortData::
lookupKey(CKeyType key_type, bool, uint *row, uint *col, bool *shift)
{
  *shift = false;

  for (*row = 0; *row < 9; ++(*row))
    for (*col = 0; *col < NUM_KEYBOARD_PORTS - 1; ++(*col))
      if (key_map_lower[*row][7 - *col] == key_type)
        return true;

  *shift = true;

  for (*row = 0; *row < 9; ++(*row))
    for (*col = 0; *col < NUM_KEYBOARD_PORTS - 1; ++(*col))
      if (key_map_upper[*row][7 - *col] == key_type)
        return true;

  cerr << "Unhandled Key: " << key_type << endl;

  return false;
}

CKeyType
CNascomPortData::
keycodeToUpper(CKeyType key_type)
{
  static uint num = sizeof(lower_upper_map)/sizeof(KeycodePair);

  for (uint i = 0; i < num; ++i) {
    if (lower_upper_map[i].keycode1 == key_type) {
      return lower_upper_map[i].keycode2;
    }
  }

  return key_type;
}

char
CNascomPortData::
keycodeToChar(CKeyType key_type)
{
  static uint num = sizeof(keycode_char)/sizeof(KeycodeChar);

  for (uint i = 0; i < num; ++i) {
    if (keycode_char[i].keycode == key_type) {
      return keycode_char[i].c;
    }
  }

  return '.';
}

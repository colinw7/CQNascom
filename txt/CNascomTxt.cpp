#include <std_c++.h>
#include <CNascom.h>
#include <CZ80RstData.h>
#include <CArgs.h>
#include <CStrUtil.h>
#include <CReadLine.h>
#include <COSTimer.h>

struct CNascomRstData : public CZ80StdRstData {
  CReadLine readline;
  int       char_num;

  CNascomRstData(CZ80 &z80) :
   CZ80StdRstData(z80), char_num(0) {
  }

  void rstFwd(unsigned short id);
};

int
main(int argc, char **argv)
{
  CNascom nascom;

  CArgs cargs("-e:i=-1 (Execute start address)");

  cargs.parse(&argc, argv);

  if (cargs.isHelp())
    exit(1);

  int e_value = cargs.getIntegerArg("-e");

  CZ80 *z80 = nascom.getZ80();

  CNascomRstData *rst_data = new CNascomRstData(*z80);

  z80->setRstData(rst_data);

  for (int i = 1; i < argc; ++i)
    z80->load(argv[i]);

  if (e_value > 0)
    z80->execute(e_value);
  else
    z80->execute();

  return 0;
}

void
CNascomRstData::
rstFwd(unsigned short id)
{
  switch (id) {
    case 0x00: { // START
      cout << "rst 00" << endl;

      char_num = 0;

      break;
    }
    case 0x08: { // RIN
      readline.setPrompt("> ");

      string line = readline.readLine();

      z80.setA(CStrUtil::toInteger(line));

      break;
    }
    case 0x10: { // RCAL
      unsigned short pc = z80.pop();

      char offset = z80.getSByte(pc++);

      z80.setPC(z80.getPC() + offset);

      z80.push(pc);

      break;
    }
    case 0x18: { // SCAL
      unsigned short pc = z80.pop();

      unsigned char id1 = z80.getByte(pc++);

      switch (id1) {
        case 0x5B: { // MRET
          cout << "MRET" << endl;

          exit(0);
        }
        case 0x5D: { // TDEL
          sleep(1);

          z80.setA(0);
          z80.setB(0);

          break;
        }
        case 0x68: { // B2HEX
          cout << CStrUtil::toHexString(z80.getA(), 2);

          char_num += 2;

          break;
        }
        case 0x69: { // SPACE
          cout << " ";

          ++char_num;

          break;
        }
        case 0x6A: { // CRLF
          cout << endl;

          char_num = 0;

          break;
        }
        case 0x6B: { // ERRM
          cout << "Error" << endl;

          char_num = 0;

          break;
        }
        case 0x7B: { // BLINK
          char c;

          cin >> c;

          z80.setA(c);

          break;
        }
        default: {
          cerr << "Unhandled rst 0x18 - " <<
                  CStrUtil::toHexString(id1, 2) << endl;
          break;
        }
      }

      z80.push(pc);

      break;
    }
    case 0x20: { // BRKPT
      z80.printState(cout);

      char_num = 0;

      break;
    }
    case 0x28: { // PRS
      unsigned short pc = z80.pop();

      unsigned char c = z80.getByte(pc++);

      while (c != '\0') {
        cout << c;

        ++char_num;

        c = z80.getByte(pc++);
      }

      z80.push(pc);

      break;
    }
    case 0x30: { // ROUT
      unsigned char c = z80.getA();

      if (c == '\r')
        c = '\n';

      if (c != '\n') {
        cout << c;

        ++char_num;
      }
      else {
        cout << endl;

        char_num = 0;
      }

      break;
    }
    case 0x38: { // RDEL
      unsigned char delay = z80.getA();

      if (delay == 0)
        delay = 255;

      COSTimer::msleep(delay*2700);

      z80.setA(0);

      break;
    }
  }

  if (char_num > 80) {
    cout << endl;

    char_num = 0;
  }

  cout.flush();
}

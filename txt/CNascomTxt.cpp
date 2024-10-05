#include <CNascom.h>
#include <CZ80RstData.h>
#include <CArgs.h>
#include <CStrUtil.h>
#include <CReadLine.h>
#include <COSTimer.h>
#include <unistd.h>

struct CNascomRstData : public CZ80StdRstData {
  CReadLine readline;
  int       char_num { 0 };

  CNascomRstData(CZ80 &z80_) :
   CZ80StdRstData(z80_) {
  }

  void rstFwd(unsigned short id) override;
};

int
main(int argc, char **argv)
{
  CNascom nascom;

  CArgs cargs("-e:i=-1 (Execute start address)");

  cargs.parse(&argc, argv);

  if (cargs.isHelp())
    exit(1);

  int e_value = int(cargs.getIntegerArg("-e"));

  CZ80 *z80 = nascom.getZ80();

  CNascomRstData *rst_data = new CNascomRstData(*z80);

  z80->setRstData(rst_data);

  for (int i = 1; i < argc; ++i)
    z80->load(argv[i]);

  if (e_value > 0)
    z80->execute(ushort(e_value));
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
      std::cout << "rst 00\n";

      char_num = 0;

      break;
    }
    case 0x08: { // RIN
      readline.setPrompt("> ");

      std::string line = readline.readLine();

      z80.setA(uchar(CStrUtil::toInteger(line)));

      break;
    }
    case 0x10: { // RCAL
      unsigned short pc = z80.pop();

      char offset = z80.getSByte(pc++);

      z80.setPC(ushort(z80.getPC() + offset));

      z80.push(pc);

      break;
    }
    case 0x18: { // SCAL
      unsigned short pc = z80.pop();

      unsigned char id1 = z80.getByte(pc++);

      switch (id1) {
        case 0x5B: { // MRET
          std::cout << "MRET\n";

          exit(0);
        }
        case 0x5D: { // TDEL
          sleep(1);

          z80.setA(0);
          z80.setB(0);

          break;
        }
        case 0x68: { // B2HEX
          std::cout << CStrUtil::toHexString(z80.getA(), 2);

          char_num += 2;

          break;
        }
        case 0x69: { // SPACE
          std::cout << " ";

          ++char_num;

          break;
        }
        case 0x6A: { // CRLF
          std::cout << "\n";

          char_num = 0;

          break;
        }
        case 0x6B: { // ERRM
          std::cout << "Error\n";

          char_num = 0;

          break;
        }
        case 0x7B: { // BLINK
          char c;

          std::cin >> c;

          z80.setA(c);

          break;
        }
        default: {
          std::cerr << "Unhandled rst 0x18 - " << CStrUtil::toHexString(id1, 2) << "\n";
          break;
        }
      }

      z80.push(pc);

      break;
    }
    case 0x20: { // BRKPT
      z80.printState(std::cout);

      char_num = 0;

      break;
    }
    case 0x28: { // PRS
      unsigned short pc = z80.pop();

      unsigned char c = z80.getByte(pc++);

      while (c != '\0') {
        std::cout << c;

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
        std::cout << c;

        ++char_num;
      }
      else {
        std::cout << "\n";

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
    std::cout << "\n";

    char_num = 0;
  }

  std::cout.flush();
}

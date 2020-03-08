#include <CNascom.h>
#include <CZ80.h>
#include <CZ80Screen.h>
#include <QWidget>

class CQZ80Dbg;
class QTimer;

class CQNascom : public QWidget, public CZ80Screen {
  Q_OBJECT

 public:
  CQNascom(CNascom *nascom, int w, int h);

 ~CQNascom();

  void exec();

  CQZ80Dbg *addDebug();

  void screenMemChanged(ushort pos, ushort len) override;

  void redraw();

  void paintEvent(QPaintEvent *) override;

  void keyPressEvent  (QKeyEvent *e) override;
  void keyReleaseEvent(QKeyEvent *e) override;

  void doSteps();

 public slots:
  void timeOut();

 private:
  CNascom*  nascom_ { nullptr };
  int       border_ { 2 };
  CQZ80Dbg* dbg_    { nullptr };
  QTimer*   timer_  { nullptr };
};

//------

class CQNascomRenderer : public CNascomRenderer {
 public:
  CQNascomRenderer(CQNascom *qnascom, QPainter *painter) :
   qnascom_(qnascom), painter_(painter) {
  }

  void clear(const CRGBA &bg) override;

  void drawImage(int x, int y, CImagePtr image) override;

 private:
  CQNascom* qnascom_ { nullptr };
  QPainter* painter_ { nullptr };
};

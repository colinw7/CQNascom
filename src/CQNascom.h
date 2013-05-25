#include <QWidget>
#include <CZ80.h>
#include <CNascom.h>

class CQNascomRenderer;

class CQNascom : public QWidget, public CZ80Screen {
  Q_OBJECT

 public:
  CQNascom(CNascom *nascom, int w, int h);

 ~CQNascom();

  CNascom *getNascom() const { return nascom_; }

  void loadChars(const std::string &filename);

  void memChanged(ushort pos, ushort len);

  void redraw();

  void paintEvent(QPaintEvent *);
  void keyPressEvent(QKeyEvent *e);
  void keyReleaseEvent(QKeyEvent *e);

 public slots:
  void timeOut();

 private:
  CNascom          *nascom_;
  int               border_;
  CQNascomRenderer *renderer_;
};

class CQNascomRenderer : public CNascomRenderer {
 public:
  CQNascomRenderer(CQNascom *qnascom);

  void loadChars(const std::string &filename);

  void setPainter(QPainter *painter);

  void clear(bool invert);

  void drawChar(int x, int y, char c);

 private:
  QImage getCharImage(char c);

  void loadChars();

  void loadImageChars(QImage image);

 private:
  CQNascom            *qnascom_;
  QPainter            *painter_;
  bool                 chars_loaded_;
  std::vector<QImage>  char_images_;
};


namespace Geometry{
      typedef double point_t;

      // ���� true, �� ����� �������������� �����������
      #define PRECISION true

      point_t eps = 1e-9, pi = acos(-1), inf = INFINITY;

      // ���������� ��� point_t � ���������� ���������� ����� � ��������� ������
      struct efloat {
          point_t value;

          efloat() {
              value = 0;
          }
          template<typename T>
          efloat(const T& value) {
              this->value = static_cast<point_t>(value);
          }

          bool operator == (const efloat& Rhs) const {
              return std::abs(value - Rhs.value) <= eps;
          }
          bool operator < (const efloat& Rhs) const {
              return value < Rhs.value - eps;
          }
          bool operator > (const efloat& Rhs) const {
              return value > Rhs.value + eps;
          }

          bool operator != (const efloat& Rhs) const {
              return !(*this == Rhs);
          }
          bool operator <= (const efloat& Rhs) const {
              return !(*this > Rhs);
          }
          bool operator >= (const efloat& Rhs) const {
              return !(*this < Rhs);
          }
      };

      #if PRECISION
      #define EFLOAT efloat
      #else
      #define EFLOAT
      #endif

      // x, y
      struct dot {
          point_t x, y;

          dot() {
              x = y = 0;
          }
          template<typename T1, typename T2>
          dot(const T1& x, const T2& y) {
              this->x = static_cast<point_t>(x);
              this->y = static_cast<point_t>(y);
          }

          dot operator + (const dot& p) const {
              return dot(x + p.x, y + p.y);
          }
          dot& operator += (const dot& p) {
              return *this = *this + p;
          }

          dot operator - (const dot& p) const {
              return dot(x - p.x, y - p.y);
          }
          dot& operator -= (const dot& p) {
              return *this = *this - p;
          }

          dot operator * (point_t k) const {
              return dot(x * k, y * k);
          }
          dot& operator *= (point_t k) {
              return *this = *this * k;
          }

          dot operator / (point_t k) const {
              return dot(x / k, y / k);
          }
          dot& operator /= (point_t k) {
              return *this = *this / k;
          }

          // ���������/����� ������������
          // ��� ������� ���������������
          point_t operator % (const dot& p) const {
              return x * p.y - y * p.x;
          }
          // ��������� ������������
          point_t operator * (const dot& p) const {
              return x * p.x + y * p.y;
          }

          point_t getQuareLen() const {
              return x * x + y * y;
          }
          point_t getLen() const {
              return sqrt(getQuareLen());
          }

          bool operator == (const dot& Rhs) const {
              return EFLOAT(x) == Rhs.x && EFLOAT(y) == Rhs.y;
          }
          bool operator != (const dot& Rhs) const {
              return !(*this == Rhs);
          }

          // ����� �����, ����� ����� ������
          bool operator < (const dot& Rhs) const {
              return EFLOAT(x) == Rhs.x ? EFLOAT(y) < Rhs.y : EFLOAT(x) < Rhs.x;
          }
          // ����� ������, ����� ����� �������
          bool operator > (const dot& Rhs) const {
              return EFLOAT(x) == Rhs.x ? EFLOAT(y) > Rhs.y : EFLOAT(x) > Rhs.x;
          }

          dot normalize(point_t mult = 1) const {
              return *this * (mult / getLen());
          }
      };

      std::istream& operator >> (std::istream& input, dot& Dot) {
          return input >> Dot.x >> Dot.y;
      }
      std::ostream& operator << (std::ostream& output, const dot& Dot) {
          return output << Dot.x << " " << Dot.y;
      }

      // ���������� ���� ����� ���������
      point_t getAngle(const dot& a, const dot& b) {
          return atan2(a % b, a * b);
      }
      // ���������� ��������������� ���� ����� ���������
      point_t getGoodAngle(const dot& a, const dot& b) {
          point_t res = getAngle(a, b);
          if (res < 0) {
              res += 2 * pi;
          }
          return res;
      }
      // ���������� ��������������� ���� ������ 180 ����� ���������
      point_t getVeryGoodAngle(const dot& a, const dot& b) {
          point_t res = getGoodAngle(a, b);
          if (res > pi) {
              res = 2 * pi - res;
          }
          return res;
      }

      // a, b, c
      class line {
          point_t a, b, c; // ax * by + c = 0
          // a � b �������������!

          // �� ��������� ������ a, b, c �������
          // ����� �������� ������� � �������
      public:

          line() {
              a = b = c = 0;
          }
          // �� ���� ������ �� ������
          line(const dot& begin, const dot& end) {
              a = begin.y - end.y;
              b = end.x - begin.x;
              // normalize
              {
                  point_t d = sqrt(a * a + b * b);
                  if (EFLOAT(d) != 0) {
                      a /= d;
                      b /= d;
                  }
              }
              c = -a * begin.x - b * begin.y;
          }
          line(point_t A, point_t B, point_t C) {
              a = A;
              b = B;
              c = C;
              // normalize
              {
                  point_t d = sqrt(a * a + b * b);
                  if(EFLOAT(d) != 0){
                      a /= d;
                      b /= d;
                      c /= d;
                  }
              }
          }

          // ���������� ������������� �� �����
          line getPerp(const dot& point) const {
              point_t A = -b, B = a;
              point_t C = -A * point.x - B * point.y;
              return line(A, B, C);
          }

          // ���������� ������������ ������ �� ���������� dist
          // ���� ��� ����� ������������, �� ������ � ������ �������
          line getParallel(point_t dist) const {
              return line(a, b, c + dist /* * sqrt(a * a + b * b)*/);
          }

          // ���������� ��������������� ������ ������ ���������� �� mult
          dot getVector(point_t mult = 1) const {
              return dot(-b, a) * mult /*.normalize(mult)*/;
          }

          // ���������� ����� ����������� ���� ������
          dot intersect(const line& Rhs) const {
              point_t x, y;
              // ax + by + c = 0
              // by = -c - ax
              // y  = (-ax - c) / b

              if (EFLOAT(Rhs.b) != 0) {
                  x = (b * Rhs.c / Rhs.b - c) / (a - b * Rhs.a / Rhs.b);
                  y = (-x * Rhs.a - Rhs.c) / Rhs.b;
              }
              else {
                  x = -Rhs.c / Rhs.a;
                  y = (-x * a - c) / b;
              }
              return dot(x, y);
          }

          // ���������� ����� ����������� ��������������
          dot perpIntersect(const dot& point) const {
              return intersect(getPerp(point));
          }

          // �������� ����� �� ������
          std::vector<dot> reflection(const std::vector<dot>& Dots) const {
              std::vector<dot> Result(Dots.size());
              for (int i = 0; i < Result.size(); i++) {
                  Result[i] = Dots[i] + (perpIntersect(Dots[i]) - Dots[i]) * 2;
              }
              return Result;
          }

          // ���������� ����� ��������������
          point_t dist(const dot& point) const {
              return abs(a * point.x + b * point.y + c) /* / std::sqrt(a * a + b * b)*/;
          }
          // �������������������� ����� ������������� �������
          point_t dist(const line& parallel) const {
              return abs(c - parallel.c) /* / sqrt(a * a + b * b)*/;
          }

          bool isParallel(const line& Rhs) const {
              return EFLOAT(a * Rhs.b - b * Rhs.a) == 0;
          }
          bool isPerp(const line& Rhs) const {
              return EFLOAT(a * Rhs.a + b * Rhs.b) == 0;
          }
          bool ison(const dot& point) const {
              return EFLOAT(a * point.x + b * point.y + c) == 0;
          }

          // ������ ���������?
          bool operator == (const line& Rhs) const {
              return (EFLOAT(a) == Rhs.a  && EFLOAT(b) == Rhs.b  && EFLOAT(c) == Rhs.c) ||
                      (EFLOAT(a) == -Rhs.a && EFLOAT(b) == -Rhs.b && EFLOAT(c) == -Rhs.c);
          }

          friend std::ostream& operator << (std::ostream& output, const line& Line);
      };

      std::istream& operator >> (std::istream& input, line& Line) {
          point_t A, B, C;
          input >> A >> B >> C;
          Line = line(A, B, C);
          return input;
      }
      std::ostream& operator << (std::ostream& output, const line& Line) {
          return output << Line.a << " " << Line.b << " " << Line.c;
      }

      // center, radius
      struct circle {
          dot center;
          point_t radius;

          circle() {
              radius = 0;
          }
          circle(const dot& center, point_t radius) {
              this->center = center;
              this->radius = radius;
          }

          // returns a point on a circle
          // counterclockwise angle
          dot point(point_t angle) const {
              return center + dot(cos(angle), sin(angle)) * radius;
          }

          // 2*pi*R
          point_t getLength() const {
              return 2 * pi * radius;
          }
          // pi*R^2
          point_t getArea() const {
              return pi * radius * radius;
          }

          // ����������� ���������� � ������
          std::vector<dot> intersect(const line& Rhs) const {
              dot perp = Rhs.perpIntersect(center),
                  delta = center - perp;

              point_t quareRadius = radius * radius;
              point_t quareDist = delta.getQuareLen();

              if (EFLOAT(quareRadius) > quareDist) { // two points
                  point_t len = sqrt(quareRadius - quareDist);
                  dot vector(Rhs.getVector(len));
                  return { dot(perp + vector), dot(perp - vector) };
              }
              else if (EFLOAT(quareRadius) == quareDist) { // one point
                  return { perp };
              }
              else { // none point
                  return {};
              }
          }

          // ����������� ���� �����������
          // ���� ������ true �� ����� ����������� ���������� �����
          bool intersect(const circle& Rhs, std::vector<dot>& result) const {
              if (Rhs.center == center) {
                  result.clear();
                  return EFLOAT(radius) == Rhs.radius;
              }
              else {
                  dot vector(Rhs.center - center);
                  line l(-2 * vector.x, -2 * vector.y, vector.getQuareLen() + radius * radius - Rhs.radius * Rhs.radius);

                  result = circle(dot(), radius).intersect(l);

                  for (auto& point : result) {
                      point += center;
                  }

                  return false;
              }
          }

          // �������� �������������� ����� ����������
          bool ison(const dot& point) const {
              return EFLOAT((center - point).getQuareLen()) == radius * radius;
          }
      };

      std::istream& operator >> (std::istream& input, circle& Circle) {
          return input >> Circle.center >> Circle.radius;
      }
      std::ostream& operator << (std::ostream& output, const circle& Circle) {
          return output << Circle.center << " " << Circle.radius;
      }

      // �������������. points
      struct polygon {
          std::vector<dot> Dots;

          polygon() {}
          polygon(const std::vector<dot>& Dots) {
              this->Dots = Dots;
          }

          // ���������� ������� ��������������
          point_t getArea() const {
              point_t result = 0;
              for (int i = 0; i < Dots.size(); i++) {
                  dot p1 = i ? Dots[i - 1] : Dots.back(),
                      p2 = Dots[i];
                  result += (p1.x - p2.x) * (p1.y + p2.y);
              }
              return std::abs(result) * 0.5;
          }

          // ���������� �������� ��������������
          point_t getPerim() const {
              point_t result = (Dots[0] - Dots.back()).getLen();
              for (int i = 1; i < Dots.size(); i++) {
                  result += (Dots[i] - Dots[i - 1]).getLen();
              }
              return result;
          }

          // �������� �� ���������� �������������� �� O(n).
          // WARNING !!No checked!!
          bool isConvexHull() const {
              int i = 2, w = 0, z = 0, sz = Dots.size();
              for(int i = 0; i < sz; i ++){
                  int j = (i - 1 + sz) % sz;
                  int k = (i - 2 + sz) % sz;
                  if(EFLOAT((Dots[i] - Dots[j]) % (Dots[j] - Dots[k])) >= 0)
                        ++ w;
                  if(EFLOAT((Dots[i] - Dots[j]) % (Dots[j] - Dots[k])) <= 0)
                        ++ z;
              }
              // ����� �������� ������ ���������
              return max(w, z) == Dots.size();
          }
      };

      // �������� ��������. polygon
      struct convexHull {
          polygon poly; // ����� �������� ��������

          convexHull() {}
          // ����������� ���������� �������� ��������
          convexHull(const polygon& newPolygon, bool isConvexHull = false) {
              poly = !isConvexHull ? buildConvexHull(newPolygon.Dots) : newPolygon;
          }

      private:

          // ���������� �������� �������� �� O(n * log n)
          std::vector<dot> buildConvexHull(std::vector<dot> Dots) {
              std::vector<dot> result;
              sort(Dots.begin(), Dots.end()); // Lhs.x == Rhs.x ? Lhs.y < Rhs.y : Lhs.x < Rhs.x

              dot start = Dots[0]; // ������
              for (auto &dot: Dots) {
                  dot -= start;
              }

              sort(Dots.begin() + 1, Dots.end(), [](const dot& Lhs, const dot& Rhs) {
                  point_t vectorProduct = Lhs % Rhs; // ���������/����� ������������ = x * p.y - y * p.x
                  if (EFLOAT(vectorProduct) == 0) { // ����� �� ����� ������
                      return EFLOAT(Lhs.getQuareLen()) < Rhs.getQuareLen();
                  }
                  else {
                      return EFLOAT(vectorProduct) < 0;
                  }
              });

              for(auto &dot : Dots) {
                  while (result.size() > 1 &&
                      EFLOAT((dot - result[result.size() - 2]) % (result.back() - result[result.size() - 2])) <= 0 /* <= ��� < ��� ��� ����������� ������*/) {
                      result.pop_back(); // ������� �������� �����, ������� ����� �� ������
                  }
                  result.push_back(dot);
              }

              for (auto &dot : result) {
                  dot += start;
              }
              return result;
          }
      };
};
using namespace Geometry;


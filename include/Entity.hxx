#include <string>
typedef std::pair<size_t, size_t> Pair;
class Entity {
private:
  Pair aLine;
  Pair aNumber;

public:

  Entity(Pair&&, Pair&&);
  Entity(const size_t&, const size_t&, const size_t&, const size_t&);
  Entity(const size_t&, const size_t&);
  size_t GetStartLine() const;
  size_t GetEndLine() const;
  void SetStartLine(const size_t&);
  void SetEndLine(const size_t&);
  size_t GetOldNum() const;
  size_t GetNewNum() const;
  Pair GetLines() const;
  void SetOldNum(const size_t&);
  void SetNewNum(const size_t&);
};

#include "Entity.hxx"

Entity::Entity(Pair&& theLine, Pair&& theNum):aLine(std::move(theLine)),aNumber(std::move(theNum))
{}

Entity::Entity(const size_t& theStartLine, const size_t& theEndLine, const size_t& theOldNum, const size_t& theNewNum)
{
  aLine.first = theStartLine;
  aLine.second = theEndLine;
  aNumber.first = theOldNum;
  aNumber.second = theNewNum;
}

Entity::Entity(const size_t& theStartLine, const size_t& theOldNum)
{
  aLine.first = theStartLine;
  aLine.second = theStartLine;
  aNumber.first = theOldNum;
  aNumber.second = theOldNum;
}

size_t Entity::GetStartLine() const
{
  return aLine.first;
}

size_t Entity::GetEndLine() const
{
  return aLine.second;
}

void Entity::SetStartLine(const size_t& theStartLine)
{
  aLine.first = theStartLine;
}

void Entity::SetEndLine(const size_t& theEndLine)
{
  aLine.second = theEndLine;
}

size_t Entity::GetOldNum() const 
{
  return aNumber.first;
}

size_t Entity::GetNewNum() const
{
  return aNumber.second;
}

Pair Entity::GetLines() const
{
  return aLine;
}

void Entity::SetOldNum(const size_t& theOldNum) 
{
  aNumber.first = theOldNum;
}

void Entity::SetNewNum(const size_t& theNewNum)
{
  aNumber.second = theNewNum;
}

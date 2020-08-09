// Parser.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <regex>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include "Entity.hxx"
#include <algorithm>

size_t FindNumber(std::string& aStr)
{
  std::cmatch aResultEnt;
  std::cmatch aResultNum;
  std::regex anRXEntity("#[0-9]+[\\s]*=");
  std::regex anRXNumber("[0-9]+");
  if (std::regex_search(aStr.c_str(), aResultEnt, anRXEntity))
    if (std::regex_search(aResultEnt.str().c_str(), aResultNum, anRXNumber))
      return std::stoi(aResultNum.str());
  return NULL;
}
void FindListOfNumber(std::vector<size_t>& theVecToFind, std::list<size_t>& theFounded, std::string theString)
{
  std::regex anRXEntity("#[0-9]+[\\s]*[\\)\\,]");
  std::regex anRXNumber("[0-9]+");
  int p = 0;
  std::cmatch aResultNum;
  for (auto anIt = std::sregex_iterator(theString.begin(), theString.end(), anRXEntity);
    anIt != std::sregex_iterator(); ++anIt)
  {
    if (std::regex_search(anIt->str().c_str(), aResultNum, anRXNumber))
    {
      bool isExist = false;
      size_t aResult = std::stoi(aResultNum.str());
      for (const auto& anIt : theFounded)
      {
        if (anIt == aResult)
        {
          isExist = true;
          break;
        }
      }
      if (!isExist)
      {
        theFounded.push_back(aResult);
        theVecToFind.push_back(aResult);
      }
    }
  }
}

int main()
{
  const char* anInputFilePath  = "D:\\LGS800_CP_ACE80H_Enclosure.STEP";
  const char* anOutputFilePath = "D:\\OutputFileTest.txt";
  size_t aStartNumber = 3395;
  const size_t aStartEntity = 4620192;

  std::string aLineCopy;
  std::string aBoundCopy;
  std::vector<Entity> aVecInputData;
  std::list<Pair> aVecStartEnd;
  std::vector<size_t> aVecToFind;
  std::list<size_t> aVecFound;
  std::list<std::string> aVecOutputData;
  std::ofstream anOutputfile;
  std::ifstream anInputFile;

  aVecToFind.push_back(aStartEntity);
  aVecFound.push_back(aStartEntity);

  anInputFile.open(anInputFilePath);
  size_t aLineCounter = 0;
  while (std::getline(anInputFile, aLineCopy))
  {
    aLineCounter++;
    size_t aStart = aLineCounter;
    size_t aCount = (aLineCopy.length() >= 15 ? 15 : aLineCopy.length());
    aBoundCopy = aLineCopy.substr(0, aCount);
    size_t aNumber = FindNumber(aBoundCopy);
    if (aNumber == 0)
      continue;
    while (aLineCopy.find(";") == std::string::npos && std::getline(anInputFile, aLineCopy)) {
      aLineCounter++;
    }
    Entity aFindEntity(aStart, aLineCounter, aNumber, aNumber);
    aVecInputData.push_back(aFindEntity);
  }
  int it = 0;
  while (!aVecToFind.empty())
  {  
    it++;
    size_t aMaxLine = aLineCounter = 0;
    aVecStartEnd.clear();
    for (const auto& anDataIter : aVecInputData)
    {
      for (auto& begin = aVecToFind.begin(); begin != aVecToFind.end(); ++begin)
      {
        if (*begin == anDataIter.GetOldNum())
        {
          aVecStartEnd.push_back(anDataIter.GetLines());
          if (aMaxLine < anDataIter.GetEndLine())
            aMaxLine = anDataIter.GetEndLine();
          aVecToFind.erase(begin);
          break;
        }
      }
    }   

    if (!aVecToFind.empty())
        return 1;
    aVecStartEnd.sort([](const Pair a, const  Pair b)->bool {return a.first < b.first; });
    Pair aTarget = aVecStartEnd.front();
    anInputFile.clear();
    anInputFile.seekg(0, std::ios::beg);
    aLineCounter = 0;
    while (!aVecStartEnd.empty() && aLineCounter <= aMaxLine && std::getline(anInputFile, aLineCopy))
    {
      aLineCounter++;
      if (aLineCounter < aTarget.first)
        continue;
      while (aLineCounter != aTarget.second && std::getline(anInputFile, aBoundCopy))
      {
        aLineCounter++;
        aLineCopy += aBoundCopy;
      }
      aLineCopy += '\n';
      FindListOfNumber(aVecToFind, aVecFound, aLineCopy);
      aVecOutputData.push_back(aLineCopy);
      aVecStartEnd.pop_front();
      aTarget = aVecStartEnd.empty() ? Pair() : aVecStartEnd.front();
    }
    std::sort(aVecToFind.begin(), aVecToFind.end());
  }
  anInputFile.close();

  anOutputfile.open(anOutputFilePath);
  for (const auto& iter : aVecOutputData)
  {
    anOutputfile << iter;
  }
  anOutputfile.close();
}


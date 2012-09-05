#include "SpanLengthEstimator.h"
#include <vector>
#include <map>
#include "util/check.hh"

using namespace std;
namespace Moses
{

void SpanLengthEstimator::AddSourceSpanScore(unsigned sourceSpanLength, float score)
{
  m_sourceScores.insert(make_pair(sourceSpanLength, score));
}

void SpanLengthEstimator::AddTargetSpanScore(unsigned targetSpanLength, float score)
{
    m_targetScores.insert(make_pair(targetSpanLength, score));
}

float SpanLengthEstimator::GetScoreBySpanLengths(unsigned sourceSpanLength, unsigned targetSpanLength) const
{
  return FetchScoreFromMap(m_sourceScores, sourceSpanLength) + FetchScoreFromMap(m_targetScores, targetSpanLength);
}

float SpanLengthEstimator::FetchScoreFromMap(const TLengthToScoreMap &lengthToScoreMap, unsigned spanLength)
{
  static const double LARGE_NUMBER = 1000.0;
  if (lengthToScoreMap.empty())
    return 0.0;
  TLengthToScoreMap::const_iterator iter = lengthToScoreMap.find(spanLength);
  if (iter == lengthToScoreMap.end())
    return -LARGE_NUMBER;
  else
    return iter->second;
}

} // namespace
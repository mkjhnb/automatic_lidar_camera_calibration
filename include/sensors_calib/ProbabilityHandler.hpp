/**
 * @file    ProbabilityHandler.hpp
 *
 * @author  btran
 *
 */

#pragma once

#include <memory>

#include "HistogramHandler.hpp"

namespace perception
{
class ProbabilityHandler
{
 public:
    using Ptr = std::shared_ptr<ProbabilityHandler>;
    using Probability = cv::Mat;
    using JointProbability = cv::Mat;

    explicit ProbabilityHandler(int numBins);
    ~ProbabilityHandler();

    bool estimateMLE(const HistogramHandler::Ptr& histogram);
    bool estimateJE(const HistogramHandler::Ptr& histogram);
    bool estimateBayes(const HistogramHandler::Ptr& histogram);

    const Probability& intensityProb() const
    {
        return m_intensityProb;
    }

    const Probability& grayProb() const
    {
        return m_grayProb;
    }

    const JointProbability& jointProb() const
    {
        return m_jointProb;
    }

    int totalPoints() const
    {
        return m_totalPoints;
    }

    double corrCoeff() const
    {
        return m_corrCoeff;
    }

 private:
    void smoothKDE();  // kernel density estimation-based smoothing

 private:
    Probability m_grayProb;
    Probability m_intensityProb;
    JointProbability m_jointProb;

    double m_corrCoeff;  // correlation coefficient
    double m_sigmaGrayBandwidth;
    double m_sigmaIntensityBandwidth;

    int m_numBins;
    int m_totalPoints;
};
}  // namespace perception

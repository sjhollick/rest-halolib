#include "TRestPowerEvent.h"
#include <algorithm>
#include <numeric>
#include <cmath>

ClassImp(TRestPowerEvent);

TRestPowerEvent::TRestPowerEvent() {}
TRestPowerEvent::~TRestPowerEvent() {}

void TRestPowerEvent::SetSpectrum(const std::vector<double>& freq,
                                  const std::vector<double>& volts) {
    fFrequency = freq;
    fVolts = volts; // store raw V_RMS values

    // Populate converted power vector (W) using conversion:
    // power (W) = (V_RMS)^2 * 8.0
    fPower.clear();
    fPower.reserve(fVolts.size());
    for (double v : fVolts) {
        fPower.push_back(v * v * 8.0);
    }

    // metadata
    if (!fFrequency.empty()) {
        fStartFrequency = fFrequency.front();
        fStopFrequency = fFrequency.back();
        if (fFrequency.size() > 1)
            fResolution = fFrequency[1] - fFrequency[0];
        else
            fResolution = 0;
    } else {
        fStartFrequency = fStopFrequency = fResolution = 0;
    }
}

double TRestPowerEvent::GetPowerAtFrequency(double f) const {
    if (fFrequency.empty() || fPower.empty()) return 0.0;
    auto it = std::lower_bound(fFrequency.begin(), fFrequency.end(), f);
    size_t idx = 0;
    if (it == fFrequency.end()) idx = fFrequency.size() - 1;
    else idx = std::distance(fFrequency.begin(), it);
    return fPower[idx];
}

double TRestPowerEvent::GetVoltsAtFrequency(double f) const {
    if (fFrequency.empty() || fVolts.empty()) return 0.0;
    auto it = std::lower_bound(fFrequency.begin(), fFrequency.end(), f);
    size_t idx = 0;
    if (it == fFrequency.end()) idx = fFrequency.size() - 1;
    else idx = std::distance(fFrequency.begin(), it);
    return fVolts[idx];
}

double TRestPowerEvent::GetMeanPower() const {
    if (fPower.empty()) return 0.0;
    double sum = std::accumulate(fPower.begin(), fPower.end(), 0.0);
    return sum / static_cast<double>(fPower.size());
}

double TRestPowerEvent::GetRmsPower() const {
    if (fPower.empty()) return 0.0;
    double mean = GetMeanPower();
    double acc = 0.0;
    for (double p : fPower) acc += (p - mean) * (p - mean);
    return std::sqrt(acc / static_cast<double>(fPower.size()));
}

double TRestPowerEvent::GetMeanVolts() const {
    if (fVolts.empty()) return 0.0;
    double sum = std::accumulate(fVolts.begin(), fVolts.end(), 0.0);
    return sum / static_cast<double>(fVolts.size());
}

double TRestPowerEvent::GetRmsVolts() const {
    if (fVolts.empty()) return 0.0;
    double mean = GetMeanVolts();
    double acc = 0.0;
    for (double v : fVolts) acc += (v - mean) * (v - mean);
    return std::sqrt(acc / static_cast<double>(fVolts.size()));
}

void TRestPowerEvent::PrintEvent() const {
    printf("TRestPowerEvent: bins=%zu start=%.3fHz stop=%.3fHz res=%.3fHz\n",
           fFrequency.size(), fStartFrequency, fStopFrequency, fResolution);
    printf("  Stored: raw volts in V_RMS (GetVolts/ GetVoltsAtFrequency) and converted power in W (GetPowers / GetPowerAtFrequency) using conversion W = V_RMS^2 * 8.0\n");
}

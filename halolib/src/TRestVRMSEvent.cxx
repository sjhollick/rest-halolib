#include "TRestVRMSEvent.h"
#include <iostream>
#include <cmath>
#include <algorithm>

ClassImp(TRestVRMSEvent);

TRestVRMSEvent::TRestVRMSEvent() {}

TRestVRMSEvent::~TRestVRMSEvent() {}

void TRestVRMSEvent::SetSpectrum(const std::vector<double>& freq,
                                     const std::vector<double>& volts) {
    // The input 'volts' vector contains V_RMS values.
    // Preserve the original V_RMS values in fVRMS
    // Optionally chop the data to conserve space
    // convert to power by:  converted = (V_RMS)^2 * 8
    fFrequency = freq;
    fVRMS = volts; 

    if (freq.size() > 1) {
        fStartFrequency = freq.front();
        fStopFrequency = freq.back();
        fResolution = freq[1] - freq[0];
    }
}

double TRestVRMSEvent::GetVoltsAtFrequency(double f) const {
    if (fFrequency.empty()) return 0.0;
    // Simple binary search for nearest bin, return volts by default
    auto it = std::lower_bound(fFrequency.begin(), fFrequency.end(), f);
    size_t idx = std::distance(fFrequency.begin(), it);

    return fVRMS[idx];
}

double TRestVRMSEvent::GetMeanVolts() const {
    if (fVRMS.empty()) return 0.0;
    double sum = 0.0;
    for (auto p : fVRMS) sum += p;
    return sum / static_cast<double>(fVRMS.size());
}

void TRestVRMSEvent::PrintEvent() {
    std::cout << "Frequency: " << fFrequency << std::endl;
    std::cout << "Volts RMS: " << fVRMS << std::endl;
}



#ifndef RestCore_TRestVRMSEvent
#define RestCore_TRestVRMSEvent

#include "TRestEvent.h"

class TRestVRMSEvent : public TRestEvent {
private:
    std::vector<double> fFrequency;   // Hz
    std::vector<double> fVRMS;       // V_RMS
    double fStartFrequency = 0;       // Hz
    double fStopFrequency = 0;        // Hz
    double fResolution = 0;           // Hz per bin
    double fTimestamp = 0;            // Unix time (optional)

public:
    TRestVRMSEvent();
    ~TRestVRMSEvent();

    // === Setters ===
    void SetSpectrum(const std::vector<double>& freq,
                     const std::vector<double>& volts);

    void SetTimestamp(double t) { fTimestamp = t; }

    // === Getters ===
    const std::vector<double>& GetFrequencies() const { return fFrequency; }
    const std::vector<double>& GetVolts() const { return fVRMS; }

    double GetStartFrequency() const { return fStartFrequency; }
    double GetStopFrequency() const { return fStopFrequency; }
    double GetResolution() const { return fResolution; }
    double GetTimestamp() const { return fTimestamp; }

    size_t GetNbins() const { return fFrequency.size(); }

    // === Utilities ===
    double GetVoltsAtFrequency(double f) const;
    double GetMeanVolts() const;

    void PrintEvent() const override;

    ClassDef(TRestVRMSEvent, 1);
};

#endif

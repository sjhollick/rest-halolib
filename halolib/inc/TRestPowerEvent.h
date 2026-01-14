#ifndef RestCore_TRestPowerEvent
#define RestCore_TRestPowerEvent

#include "TRestEvent.h"

// TRestPowerEvent
// A self-contained event that accepts input as V_RMS (volts) and
// stores both the raw volts vector and a converted power vector (watts).
// Conversion implemented here: power (W) = (V_RMS)^2 * 8.0

class TRestPowerEvent : public TRestEvent {
private:
    std::vector<double> fFrequency;    // Hz
    std::vector<double> fVolts;        // V_RMS (raw input)
    std::vector<double> fPower;        // W (converted = volts^2 * 8)
    double fStartFrequency = 0;        // Hz
    double fStopFrequency = 0;         // Hz
    double fResolution = 0;            // Hz per bin
    double fTimestamp = 0;             // Unix time (optional)

public:
    TRestPowerEvent();
    ~TRestPowerEvent();

    // === Setters ===
    // Accepts frequencies (Hz) and volts (V_RMS). The implementation
    // fills both fVolts (raw) and fPower (converted Watts = v^2 * 8).
    void SetSpectrum(const std::vector<double>& freq,
                     const std::vector<double>& volts);

    void SetTimestamp(double t) { fTimestamp = t; }

    // === Getters ===
    const std::vector<double>& GetFrequencies() const { return fFrequency; }
    const std::vector<double>& GetVolts() const { return fVolts; }
    const std::vector<double>& GetPowers() const { return fPower; }

    double GetStartFrequency() const { return fStartFrequency; }
    double GetStopFrequency() const { return fStopFrequency; }
    double GetResolution() const { return fResolution; }
    double GetTimestamp() const { return fTimestamp; }

    size_t GetNbins() const { return fFrequency.size(); }

    // === Utilities ===
    // Return power (W) at nearest frequency bin. Returns 0 if empty.
    double GetPowerAtFrequency(double f) const;
    // Return volts (V_RMS) at nearest frequency bin. Returns 0 if empty.
    double GetVoltsAtFrequency(double f) const;

    // Statistics
    double GetMeanPower() const;   // mean over fPower (W)
    double GetRmsPower() const;    // RMS over fPower (W)
    double GetMeanVolts() const;   // mean over fVolts (V)
    double GetRmsVolts() const;    // RMS over fVolts (V)

    void PrintEvent() const override;

    ClassDef(TRestPowerEvent, 1);
};

#endif

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include "TRestPowerEvent.h"

int main() {
    TRestPowerEvent e;

    std::vector<double> freq = {10.0, 20.0, 30.0, 40.0};
    std::vector<double> volts = {0.5, 1.0, 0.25, 2.0};

    e.SetSpectrum(freq, volts);

    const auto &p = e.GetPowers();
    const auto &v = e.GetVolts();

    const double tol = 1e-12;
    for (size_t i = 0; i < v.size(); ++i) {
        double expected = v[i] * v[i] * 8.0;
        if (std::abs(p[i] - expected) > tol) {
            std::cerr << "Conversion mismatch at " << i << ": got " << p[i]
                      << " expected " << expected << "\n";
            return 2;
        }
    }

    double f = 25.0;
    double p_at = e.GetPowerAtFrequency(f);
    double v_at = e.GetVoltsAtFrequency(f);
    std::cout << "Power at " << f << " Hz = " << p_at << " W; Volts = " << v_at << " V\n";

    double meanV = e.GetMeanVolts();
    double meanP = e.GetMeanPower();
    std::cout << "Mean V: " << meanV << "  Mean P: " << meanP << "\n";

    TRestPowerEvent empty;
    assert(empty.GetMeanVolts() == 0.0);
    assert(empty.GetMeanPower() == 0.0);
    assert(empty.GetPowerAtFrequency(10.0) == 0.0);

    std::cout << "All checks passed." << std::endl;
    return 0;
}

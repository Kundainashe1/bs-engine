#include <iostream>
#include <iomanip>
#include "black_scholes.h"
#include "OptionContract.h"

int main() {
    try {
        OptionContract call(7500, 7600, 0.25, 0.0525, 0.18, OptionType::Call);
        OptionContract put (7500, 7600, 0.25, 0.0525, 0.18, OptionType::Put);

        std::cout << std::fixed << std::setprecision(4);

        std::cout << "Call price: "
                  << bsCall(call.spot(), call.strike(), call.timeToExpiry(),
                             call.rate(), call.volatility()) << "\n";

        std::cout << "Put  price: "
                  << bsPut(put.spot(), put.strike(), put.timeToExpiry(),
                            put.rate(), put.volatility()) << "\n";

        // Now test RAII — this should throw and be caught
        OptionContract bad(7500, -100, 0.25, 0.05, 0.18, OptionType::Call);

    } catch (const std::exception& e) {
        std::cerr << "Contract error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}

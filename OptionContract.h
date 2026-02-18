#pragma once
#include <string>
#include <stdexcept>
 
enum class OptionType { Call, Put };   // scoped enum — no namespace pollution
enum class ExerciseStyle { European, American };
 
class OptionContract {
public:
    // Constructor validates ALL inputs immediately — RAII principle.
    // If construction succeeds, the object is guaranteed valid. Always.
    OptionContract(double spot, double strike, double timeToExpiry,
                   double riskFreeRate, double volatility,
                   OptionType type, ExerciseStyle style = ExerciseStyle::European)
        : S_(spot), K_(strike), T_(timeToExpiry),
          r_(riskFreeRate), sigma_(volatility),
          type_(type), style_(style)
    {
        // Validate in constructor — not in a separate validate() method.
        // A half-constructed object is a liability.
        if (S_ <= 0)     throw std::invalid_argument("Spot must be positive");
        if (K_ <= 0)     throw std::invalid_argument("Strike must be positive");
        if (T_ <= 0)     throw std::invalid_argument("Time to expiry must be positive");
        if (sigma_ <= 0) throw std::invalid_argument("Volatility must be positive");
    }
 
    // Const getters — the contract cannot be mutated after construction.
    double     spot()        const { return S_; }
    double     strike()      const { return K_; }
    double     timeToExpiry()const { return T_; }
    double     rate()        const { return r_; }
    double     volatility()  const { return sigma_; }
    OptionType type()        const { return type_; }
    bool       isCall()      const { return type_ == OptionType::Call; }
    ExerciseStyle style()    const { return style_; }
    
 
private:
    // Trailing underscores mark member variables — industry convention.
    // Private means the only way in is through the validated constructor.
    double S_, K_, T_, r_, sigma_;
    OptionType type_;
    ExerciseStyle style_;
};

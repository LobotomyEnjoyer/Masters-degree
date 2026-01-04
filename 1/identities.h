#ifndef IDENTITIES_H
#define IDENTITIES_H

#include<array>

// x^2 = x
bool iden1(std::array<std::array<int,16>,16> K);

// xy = yx
bool iden2(std::array<std::array<int,16>,16> K);

// x^2*y^2 = y^2*x^2
bool iden3(std::array<std::array<int,16>,16> K);

// x^2*y = xy
bool iden4(std::array<std::array<int,16>,16> K);

// xy = x*y^2
bool iden4_star(std::array<std::array<int,16>,16> K);

// xyz = yxz
bool iden5(std::array<std::array<int,16>,16> K);

// xy ≤ y
bool iden6(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O);

// xy ≤ x
bool iden6_star(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O);

// xy ≤ y^2
bool iden7(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O);

// xy ≤ x^2
bool iden7_star(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O);

// x ≤ yz ⇒ x ≤ yx
bool quasi_iden8(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O);

// (x ≤ y^2 ∧ x ≤ z^2) ⇒ x ≤ yz
bool quasi_iden9(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O);

// (x ≤ yz ∧ x ≤ wv) ⇒ x ≤ yv
bool quasi_iden10(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O);

#endif
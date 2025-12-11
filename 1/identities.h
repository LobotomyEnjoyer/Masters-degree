#ifndef IDENTITIES_H
#define IDENTITIES_H

#include<array>

// (xy)z = x(yz)
bool iden1(std::array<std::array<int,16>,16> K);

// xy = yx
bool iden2(std::array<std::array<int,16>,16> K);

// x^2y = yx
bool iden3(std::array<std::array<int,16>,16> K);

// xy^2 = yx
bool iden4(std::array<std::array<int,16>,16> K);

// (xy)z = (yx)z
bool iden5(std::array<std::array<int,16>,16> K);

// x(yz) = x(zy)
bool iden6(std::array<std::array<int,16>,16> K);

// ((xy)z)w = (x(yz))w
bool iden7(std::array<std::array<int,16>,16> K);

// x((yz)w) = x(y(zw))
bool iden8(std::array<std::array<int,16>,16> K);

// x((yz)w) = x(y(zw))
bool iden9(std::array<std::array<int,16>,16> K);

// xy ≤ x
bool iden10(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O);

// xy ≤ y
bool iden11(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O);

// x ≤ yz ⇒ x ≤ xz
bool quasi1(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O);

// x ≤ yz ⇒ x ≤ yx
bool quasi2(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O);

// x ≤ yz ∧ x ≤ uw ⇒ x ≤ yw
bool quasi3(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O);

#endif
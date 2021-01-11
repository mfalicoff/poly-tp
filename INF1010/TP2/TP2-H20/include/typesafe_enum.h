#ifndef TYPESAFEENUM_H
#define TYPESAFEENUM_H

//! Noter que pour �tre "type safe" l'�num�ration utilis�e devrait �tre une "enum class" (C++11)
//! malgr� que enum_value accepte aussi les anciennes "enum". Pour utiliser to_enum, conversion
//! s�curitaire d'un entier vers une �num�ration, les �num�rations doivent utiliser des valeurs
//! contigues et avoir deux valeurs sp�ciales, first_ et last_, qui correspondent � la premi�re
//! (plus petite) et derni�re (plus grande) valeur de l'�num�ration.  Ceci requiert une "enum class"
//! sinon il y aura plusieurs d�finitions de first_ et last_.
//! \author Francois-R.Boyer@PolyMtl.ca
//! \date   2019-02

#include <cassert>
#include <type_traits>

//! Donne la valeur num�rique qui correspond � une valeur d'�num�ration, dans le bon type
//! sous-jacent.
template<typename Enum>
constexpr auto enum_value(Enum x)
{
	static_assert(
		std::is_enum_v<Enum>); // Pas n�cessaire pour avoir une erreur de compilation, la ligne
							   // ci-dessous �choue d�j� si ce n'est pas une enum, mais �a permet
							   // d'avoir l'appel � cette fonction dans le message d'erreur.
	// NOTE: Devrait utiliser un "concept" C++20 au lieu de static_assert, le message d'erreur
	// devrait �tre encore meilleur.
	return static_cast<std::underlying_type_t<Enum>>(x);
}

//! Suppose que l'Enum contient des valeurs first_ et last_, et que toutes les valeurs entre sont
//! valides.
template<typename Enum, typename T>
constexpr bool valid_as_enum(T x)
{
	static_assert(std::is_enum_v<Enum>);
	static_assert(std::is_integral_v<T>);
	using type_used_for_comparison = decltype(T{} +std::underlying_type_t<Enum>{});
	bool can_be_represented_in_used_type = std::is_signed_v<type_used_for_comparison> || x >= T{};
	auto casted_value = static_cast<type_used_for_comparison>(x);
	return can_be_represented_in_used_type && casted_value >= enum_value(Enum::first_) &&
		casted_value <= enum_value(Enum::last_);
}

//! Suppose que l'Enum contient des valeurs first_ et last_, et que toutes les valeurs entre sont
//! valides.
template<typename Enum, typename T>
constexpr Enum to_enum(T x)
{
	assert(valid_as_enum<Enum>(x));
	return Enum(x);
}

#endif


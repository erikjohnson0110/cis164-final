#ifndef ENUMS_H
#define ENUMS_H
#include <string>

enum class Weight
{
    Ounce,
    Pound,
    Gram,
    Milligram,
    Kilogram
};

enum class Volume
{
    Ounce,
    Gallon,
    Quart,
    Pint,
    Liter,
    Milliliter
};

enum class MachineModel
{
    TK421,
    VM4000,
    Vendtron20,
    FoodBoxXD
};

const std::string weightNames[] = {"Ounce", "Pound", "Gram", "Milligram", "Kilogram"};
const std::string volumeNames[] = {"Ounce", "Gallon", "Quart", "Pint", "Liter", "Milliliter"};
const std::string machineModelNames[] = {"TK421", "VM4000", "Vendtron20", "FoodBoxXD"};

#endif // ENUMS_H

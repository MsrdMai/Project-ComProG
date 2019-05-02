#include "Inventory.h"
#include <stdio.h>



Inventory::Inventory()
{
}


Inventory::~Inventory()
{
}

void Inventory::addPlant(int type)
{
	plantproduct[type] += 1;
}

void Inventory::useWater()
{
	water -= 1;
}

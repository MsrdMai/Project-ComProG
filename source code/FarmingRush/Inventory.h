#pragma once
class Inventory
{
public:
	Inventory();
	~Inventory();

	static void addPlant(int type);
	static void useWater();

public:
	static int plantproduct[10];
	static int animalproduct[10];
	static int money;
	static int water;
	static int animalfood;
	static int seed[10];
	static int animalstock[10];

};


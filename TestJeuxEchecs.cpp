// Fichier de test pour le projet Jeux d'�checs
// Ce fichier contient les tests unitaires pour le projet Jeux d'�checs.
// Pour le moment, il y a seulement des tests d'exemple.
// Vous devez ajouter vos propres tests pour v�rifier le bon fonctionnement de votre code.
// 
// 
//
// Include ici les headers de votre partie de code � tester

#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#endif
#ifdef TEST

TEST(Test, exempleDeTest)
{
	EXPECT_EQ(1, 1);
}

TEST(Test, exempleDeTest2)
{
	EXPECT_FALSE(1 == 2);
}

#endif
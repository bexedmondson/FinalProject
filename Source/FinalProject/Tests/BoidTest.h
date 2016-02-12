// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class FINALPROJECT_API BoidTest
{
public:
	BoidTest();

	IMPLEMENT_SIMPLE_AUTOMATION_TEST(BoidTest, "Boid", ATF_Game)

	bool RunTest(FString& Parameters);
};

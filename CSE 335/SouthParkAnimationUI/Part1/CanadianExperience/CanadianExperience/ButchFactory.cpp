/**
 * \file ButchFactory.cpp
 *
 * \author Charles Bean
 */

#include "stdafx.h"
#include "ButchFactory.h"
#include "ImageDrawable.h"
#include "PolyDrawable.h"
#include "HeadTop.h"

using namespace std;

/** \brief Constructor */
CButchFactory::CButchFactory()
{
}

/** \brief Destructor */
CButchFactory::~CButchFactory()
{
}

/** \brief This is a concrete factory method that creates our Butch actor.
* \returns Pointer to an actor object.
*/
std::shared_ptr<CActor> CButchFactory::Create()
{
	/** Initializing **/

	// Create the butch actor
	shared_ptr<CActor> actor = make_shared<CActor>(L"Butch");


	/** Creating Parts **/

	// Add shirt
	auto shirt = make_shared<CImageDrawable>(L"Shirt", L"images/butch_armor.png");
	shirt->SetCenter(Point(44, 138));
	shirt->SetPosition(Point(0, -114));
	actor->SetRoot(shirt);

	// Add left leg
	auto lleg = make_shared<CImageDrawable>(L"Left Leg", L"images/butch_lleg.png");
	lleg->SetCenter(Point(11, 9));
	lleg->SetPosition(Point(54, 0));
	shirt->AddChild(lleg);

	// Add right leg
	auto rleg = make_shared<CImageDrawable>(L"Right Leg", L"images/butch_rleg.png");
	rleg->SetCenter(Point(39, 9));
	rleg->SetPosition(Point(0, 0));
	shirt->AddChild(rleg);

	// Add left arm
	auto larm = make_shared<CPolyDrawable>(L"Left Arm");
	larm->SetColor(Color::Green);
	larm->SetPosition(Point(80, -110));
	larm->AddPoint(Point(-7, -7)); 	// Upper left point
	larm->AddPoint(Point(-7, 96)); 	// Lower left point
	larm->AddPoint(Point(8, 96));   // Upper right point
	larm->AddPoint(Point(8, -7));   // Lower right point 
	shirt->AddChild(larm);

	// Add right arm
	auto rarm = make_shared<CPolyDrawable>(L"Right Arm");
	rarm->SetColor(Color::Green);
	rarm->SetPosition(Point(-25, -110));
	rarm->AddPoint(Point(-7, -7));
	rarm->AddPoint(Point(-7, 96));
	rarm->AddPoint(Point(8, 96));
	rarm->AddPoint(Point(8, -7));
	shirt->AddChild(rarm);

	// Add left hand
	auto lhand = make_shared<CPolyDrawable>(L"Left Hand");
	lhand->SetColor(Color(253, 218, 180));
	lhand->SetPosition(Point(0, 96));
	lhand->AddPoint(Point(-12, -2));
	lhand->AddPoint(Point(-12, 17));
	lhand->AddPoint(Point(11, 17));
	lhand->AddPoint(Point(11, -2));
	larm->AddChild(lhand);

	// Add right hand
	auto rhand = make_shared<CPolyDrawable>(L"Right Hand");
	rhand->SetColor(Color(253, 218, 180));
	rhand->SetPosition(Point(0, 96));
	rhand->AddPoint(Point(-12, -2));
	rhand->AddPoint(Point(-12, 17));
	rhand->AddPoint(Point(11, 17));
	rhand->AddPoint(Point(11, -2));
	rarm->AddChild(rhand);
	
	// Add head bottom
	auto headb = make_shared<CImageDrawable>(L"Head Bottom", L"images/butch_headb.png");
	headb->SetCenter(Point(24, 31));
	headb->SetPosition(Point(0, -130));
	shirt->AddChild(headb);

	// Add head top
	auto headt = make_shared<CHeadTop>(L"Head Top", L"images/butch_headt.png");
	headt->SetCenter(Point(55, 109));
	headt->SetPosition(Point(0, -31));
	headt->SetEyes(Point(90, 80), Point(62, 80)); //< Set the eyes position
	headt->SetLeftEyebrow(Point(52, 61), Point(64, 61)); // Set the left eyebrow position
	headt->SetRightEyebrow(Point(85, 60), Point(95, 61)); // Set the right eyebrow position
	headb->AddChild(headt);


	/** Adding Parts **/

	// Add the drawables (IN ORDER)
	actor->AddDrawable(lleg);
	actor->AddDrawable(rleg);
	actor->AddDrawable(larm);
	actor->AddDrawable(rarm);
	actor->AddDrawable(rhand);
	actor->AddDrawable(lhand);
	actor->AddDrawable(shirt);
	actor->AddDrawable(headb);
	actor->AddDrawable(headt);


	// Return shared_ptr to butch
	return actor;
}

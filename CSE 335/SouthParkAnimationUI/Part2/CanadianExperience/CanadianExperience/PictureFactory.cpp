/**
 * \file PictureFactory.cpp
 *
 * \author Charles Bean
 */

#include "stdafx.h"
#include "PictureFactory.h"
#include "HaroldFactory.h"
#include "ImageDrawable.h"
#include "ButchFactory.h"

#include <memory>

using namespace std;

/** \brief Constructor*/
CPictureFactory::CPictureFactory()
{
}

/** \brief Destructor */
CPictureFactory::~CPictureFactory()
{
}

/** \brief Factory method to create a new picture.
* \returns The created picture
*/
std::shared_ptr<CPicture> CPictureFactory::Create()
{
	shared_ptr<CPicture> picture = make_shared<CPicture>();

	// Create the background and add it
	auto background = make_shared<CActor>(L"Background");
	background->SetClickable(false);
	background->SetPosition(Point(-100, 0));
	auto backgroundI = make_shared<CImageDrawable>(L"Background", L"images/Background.png");
	background->AddDrawable(backgroundI);
	background->SetRoot(backgroundI);
	picture->AddActor(background);

	
	/** Adding Harold **/

	// Create and add Harold
	CHaroldFactory factory;
	auto harold = factory.Create();

	// This is where Harold will start out.
	harold->SetPosition(Point(400, 500));

	picture->AddActor(harold);


	/** Adding Butch **/

	// Create and add Butch
	CButchFactory butchFactory;
	auto butch = butchFactory.Create();

	// Where butch begins
	butch->SetPosition(Point(650, 600));

	// Add butch to picture
	picture->AddActor(butch);

	return picture;
}
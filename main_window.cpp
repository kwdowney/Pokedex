#include "main_window.h"

MainWindow::MainWindow()
{
	// Title
	setWindowTitle("Pokedex");

	// Overall layout
	overallLayout = new QHBoxLayout();

	// // Selected pokemon display
	// Layout
	pokemonDisplayLayout = new QVBoxLayout();
	overallLayout->addLayout(pokemonDisplayLayout);

	// Pokemon image
	pokemonImageContainer = new QLabel();
	pokemonDisplayLayout->addWidget(pokemonImageContainer);

	// Pokemon name
	pokemonNameDisplay = new QLabel();
	pokemonDisplayLayout->addWidget(pokemonNameDisplay);

	// Make it so image and name are at the top
	pokemonDisplayLayout->addStretch();

	// // List of all pokemon
	pokemonListWidget = new QListWidget();
	overallLayout->addWidget(pokemonListWidget);
	connect(pokemonListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(displayPokemon(int)));

	// // Form to add pokemon
	// Layout
	formLayout = new QVBoxLayout();
	overallLayout->addLayout(formLayout);

	// Pokemon name label
	pokemonNameLabel = new QLabel("Pokemon's Name:");
	formLayout->addWidget(pokemonNameLabel);

	// Pokemon name input
	pokemonNameInput = new QLineEdit();
	formLayout->addWidget(pokemonNameInput);

	// Image filename label
	imageFilenameLabel = new QLabel("Image Filename:");
	formLayout->addWidget(imageFilenameLabel);

	// Image filename input
	imageFilenameInput = new QLineEdit();
	formLayout->addWidget(imageFilenameInput);

	// Add button
	addButton = new QPushButton("Add Pokemon");
	connect(addButton, SIGNAL(clicked()), this, SLOT(addPokemon()));
	formLayout->addWidget(addButton);

	// Set overall layout
	setLayout(overallLayout);
}

MainWindow::~MainWindow()
{
	// Delete the images
	for(std::vector<QImage*>::iterator i = pokemonImages.begin();
		i != pokemonImages.end();
		++i)
	{
		delete *i;
	}
/*
	delete overallLayout;
	delete pokemonDisplayLayout;
	delete pokemonImageContainer;
	delete pokemonNameDisplay;

	delete pokemonListWidget;

	// Form for new quote
	delete formLayout;
	delete pokemonNameLabel;
	delete pokemonNameInput;
	delete imageFilenameLabel;
	delete imageFilenameInput;
	delete addButton;
*/	
}

void MainWindow::addPokemon()
{
	// Do nothing if user left at least one input blank
	if(pokemonNameInput->text().isEmpty() || imageFilenameInput->text().isEmpty())
	{
		return;
	}

	// // Get form values
	// Pokemon name
	QString name = pokemonNameInput->text();
	
	// Image
	QString filename = imageFilenameInput->text();
	QImage* newImage = new QImage();

	newImage->load(filename);
	pokemonImages.push_back(newImage);

	// Create a new list item with the pokemon's name
	pokemonNames.push_back(name.toStdString());

	pokemonListWidget->addItem(name);


	// Clear the form inputs
	pokemonNameInput->setText("");
	imageFilenameInput->setText("");
}

void MainWindow::displayPokemon(int pokemonIndex)
{
	// Get the pokemon specified by the index,
	// which is passed into the function when
	// the user clicks on pokemonListWidget

	// Image
	QImage* pokemonImage = pokemonImages[pokemonIndex];
	pokemonImageContainer->setPixmap(QPixmap::fromImage(*pokemonImage));

	// Pokemon name
	QString pokemonName;
	pokemonName = QString::fromStdString(pokemonNames[pokemonIndex]);
	pokemonNameDisplay->setText(pokemonName);
}
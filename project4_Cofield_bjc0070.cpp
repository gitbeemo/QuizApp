#include <algorithm>
#include <iostream>

using namespace std;

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/* Structures */
struct Choice {
	string text;
	Choice* next;
};

struct Question {
	string type; // question type
	string question;
	string correctAnswer;
	double pointValue;
	Choice* choices;
};

struct Node {
	Question question;
	Node* next;
};

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/* Create */
Choice* createChoice(const std::string& choiceText) {
	Choice* newChoice = new Choice;
	newChoice->text = choiceText;
	newChoice->next = nullptr;
	return newChoice;
}

Node* createNode(const Question& q) {
	Node* newNode = new Node;
	newNode->question = q;
	newNode->next = nullptr;
	return newNode;
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/* Add MCQ Choice */
void addChoice (Question& q) {
	string choiceText;
	bool hasChoice = false;
	Choice* lastChoice = nullptr;
	for (int i = 0; i < 10; ++i) {
		cout << "Enter choice " << char('A' + i) << ": ";
		getline(cin, choiceText);
		if (choiceText == "quit()" && hasChoice) {
			break;
		} else if (choiceText == "quit()" && !hasChoice) {
			cout << "Add one choice before quitting.\n";
			--i;
			continue;
		}
		Choice* newChoice = createChoice(choiceText);

		if (!q.choices) {
			// If first choice, set as head
			q.choices = newChoice;
		} else {
			lastChoice-> next = newChoice; //Append at the end
		}


		lastChoice = newChoice;
		hasChoice = true;
	}
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/* Function to check correct answer for MCQ */
bool isCorrectAnswer(Question& q, const string& correctAnswer) {
	Choice* current = q.choices;
	char correctChar = tolower(correctAnswer[0]);
	char allowedChar = 'a';
	while (current != nullptr) {
		if (correctChar == allowedChar) return true;
		current = current->next;
		++allowedChar;
	}
	return false;
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/* Function to add a question to linked list */
void addQuestion (Node*& head) {
	Question q;
	q.choices = nullptr; // init the choices ptr

	// Prompt user type of question
	while (true) {
		cout << "Type of question [mcq/tf/wr]: ";
		cin >> q.type;

		if (q.type == "mcq" || q.type == "tf" || q.type == "wr") {
			break;
		} else {
			cout << "[Command not recognized, please try again!]\n\n";
		}
	}
	cin.ignore();

	cout << "Enter a question: ";
	getline(cin, q.question);

	if (q.type == "mcq") {
		cout << "[At any time, type 'quit()' to exit]\n";
		addChoice(q);
		while (true) {
			cout << "Select correct answer: ";
			cin >> q.correctAnswer;
			transform(q.correctAnswer.begin(), q.correctAnswer.end(), q.correctAnswer.begin(), ::tolower);

			if (isCorrectAnswer(q, q.correctAnswer)) {
				break;
			}
			cout << "[Answer not recognized, please try again!]\n";
		}
		transform(q.correctAnswer.begin(), q.correctAnswer.end(), q.correctAnswer.begin(), ::tolower);

	} else if (q.type == "tf") {
		while (true) {
			cout << "Select correct answer: ";
			cin >> q.correctAnswer;
			transform(q.correctAnswer.begin(),q.correctAnswer.end(), q.correctAnswer.begin(), ::tolower);
			if (q.correctAnswer == "true" || q.correctAnswer == "false") {
				break;

			}
			cout << "[Answer not recognized, please try again!]\n";
		}
	} else if (q.type == "wr") {
		cout << "Type correct answer: ";
		getline(cin, q.correctAnswer);
	}

	cout << "Enter point value: ";

	while ( !(cin >> q.pointValue) || q.pointValue <= 0.0) {
		cout << "[Not a point value, please try again!]\n";
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Enter point value: ";
	}
	cin.ignore();

	Node* newNode = createNode(q);
	newNode -> next = head;
	head = newNode;
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/* Function to add a edit questions from a linked list */
void editQuestion(Node* head) {
	// Pull total questions
	int totalQuestions = 0;
	Node* current = head;
	while (current != nullptr) {
		totalQuestions++;
		current = current->next;
	}

	string input;
	int questionNumber = -1;

	// Prompt until valid input or "quit()" is entered
	while (true) {
		cout << "Select a question to edit, or type quit() [1-" << totalQuestions << "]: ";
		cin >> input;
		cin.ignore();

		if (input == "quit()") {
			return;
		}

		try {
			questionNumber = stoi(input);
			if (questionNumber >= 1 && questionNumber <= totalQuestions) {
				break; // Valid input, exit loop
			} else {
				cout << "[That question does not exist! Try again.]\n";
			}
		} catch (invalid_argument&) {
			cout << "[Invalid input! Please enter a valid question number or quit().]\n";
		}
	}

	// Go to selected question
	current = head;
	for (int i = 1; i < questionNumber && current != nullptr; i++) {
		current = current->next;
	}

	if (current != nullptr) {
		cout << "===============================\n"
			 << "=== QUESTION " << questionNumber << " ===\n"
			 << "===============================\n";
		cout << "1. Type: " << current->question.type << "\n";
		cout << "2. Question: " << current->question.question << "\n";
		cout << "3. Answer choices:\n";

		// Display answer choices if type is "mcq"
		if (current->question.type == "mcq") {
			Choice* choice = current->question.choices;
			char option = 'A';
			while (choice != nullptr) {
				cout << option << ". " << choice->text << endl;
				choice = choice->next;
				++option;
			}
		} else {
			cout << "    [No choices available for this question type.]\n";
		}

		cout << "4. Correct answer: " << current->question.correctAnswer << "\n";

		// Edit specific fields
		cout << "Type a number to edit, or type quit(): ";
		cin >> input;
		cin.ignore();

		if (input == "quit()") {
			return;
		}

		try {
			int fieldToEdit = stoi(input);

			if (fieldToEdit == 1) {
				cout << "Enter a new question type: ";
				cin >> current->question.type;
				cin.ignore();
			} else if (fieldToEdit == 2) {
				cout << "Enter a new question: ";
				getline(cin, current->question.question);
			} else if (fieldToEdit == 3 && current->question.type == "mcq") {
				Choice* choice = current->question.choices;
				char option = 'A';
				while (choice != nullptr) {
					cout << "Enter new text for choice " << option << ": ";
					getline(cin, input);
					if (input == "quit()") {
						return;
					}
					choice->text = input;
					choice = choice->next;
					++option;
				}
			} else if (fieldToEdit == 3) {
				cout << "[No choices to edit for this question type.]\n";
			} else if (fieldToEdit == 4) {
				cout << "Enter new correct answer: ";
				getline(cin, current->question.correctAnswer);
			} else {
				cout << "[Not recognized. No changes made.]\n";
			}
		} catch (invalid_argument&) {
			cout << "[Invalid input! Please enter a valid option number or quit().]\n";
		}
	} else {
		cout << "[No such question exists!]\n";
	}
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/* Function to delete a question from a  linked list */
void deleteQuestion(Node*& head) {
	// Pull total questions
	int totalQuestions = 0;
	Node* current = head;
	while (current != nullptr) {
		totalQuestions++;
		current = current->next;
	}

	int questionNumber;
	cout << "Select a question to delete [1-" << totalQuestions << "]: ";
	cin >> questionNumber;
	cin.ignore();

	if (questionNumber <= 0) {
		cout << "[That question does not exist!]\n";
		return;
	}

	current = head;
	Node* previous = nullptr;
	for (int i = 1; i < questionNumber && current != nullptr; ++i) {
		previous = current;
		current = current->next;
	}

	if (current != nullptr) {
		if (previous == nullptr) {
			head = current->next;
		} else {
			previous->next = current->next;
		}
		delete current;
		cout << "Question " << questionNumber << " deleted.\n";
	} else {
		cout << "[No such question exists!]\n";
	}
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/* Display Session Log */
void displaySessionLog(Node*& head) {
	Node* current = head;
	int totalQuestions = 0;
	double totalPointValues = 0.0;

	cout << "=== Session Log ===\n";
	while (current != nullptr) {
		totalQuestions++;
		totalPointValues += current -> question.pointValue;
		current = current -> next;
	}


	cout << "Total questions: " << totalQuestions;
	cout << "\nTotal point values: " << totalPointValues;
	cout << "\n\n";
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/* Reverse list back to its order */
void reverseList(Node*& head) {
	Node* prev = nullptr;
	Node* current = head;
	Node* next = nullptr;
	while (current != nullptr) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	head = prev;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/* Assessment */
void startAssessment (Node* head) {
	Node* current = head;
	double totalPoints = 0.0, score = 0.0;
	int totalQuestions = 0, correctQuestions = 0;
	int qNumber = 1;

	while (current != nullptr) {
		cout << "Question " << qNumber << ": ";
		cout << current -> question.question << endl;

		if (current -> question.type == "mcq") {
			Choice* choice = current -> question.choices;
			char option = 'A';
			while (choice != nullptr) {
				cout << option << ". " << choice -> text << endl;
				choice = choice -> next;
				++option;
			}
		}

		string userAnswer;

		// cin >> for non-wr and
		if (current -> question.type == "wr") {
			cout << "Your answer: ";
			cin.ignore();
			getline(cin, userAnswer);
		} else {
			cout << "Your answer: ";
			cin >> userAnswer;
			cin.ignore();
		}
		transform(userAnswer.begin(), userAnswer.end(), userAnswer.begin(), ::tolower);

		if (userAnswer == current -> question.correctAnswer) {
			cout << "[Your answer is correct!]";
			score += current -> question.pointValue;
			correctQuestions++;
		} else {
			cout << "[Your answer is incorrect. The correct answer is " << current -> question.correctAnswer << ".]";
		}

		totalPoints += current -> question.pointValue;
		++qNumber;
		++totalQuestions;
		current = current -> next;

		cout << endl;


	}

	cout << "=== Session Log ===\n";
	cout << "Correct answers: " << correctQuestions << " / " << totalQuestions;
	cout << "\nFinal score: " << score << " / " << totalPoints;
	cout << "\n\n";
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/* Main Function */
int main () {
	Node* head = nullptr; // init the node ptr
	int choice;
	bool exitProgram = false;

	cout << "*** Welcome to Ben's Testing Service ***\n\n";

	do {
		cout << "Do you want to?\n" <<
			"  1. Create new question.\n" <<
			"  2. Edit question.\n" <<
			"  3. Delete question.\n" <<
			"  4. Finish.\n";
		cout << "Select an action: ";
		cin >> choice;
		cin.ignore();

		switch(choice) {
			case 1:
				addQuestion(head);
				cout << "Question saved.\n\n";
				break;;
			case 2:
				editQuestion(head);
				break;
			case 3:
				deleteQuestion(head);
				break;
			case 4:
				displaySessionLog(head);
				exitProgram = true;
				break;

		}
	} while (!exitProgram);

		//Start the Assessment
	char beginAssessment;
	cout << "<!> Begin assessment? [y/n]:";
	cin >> beginAssessment;
	cin.ignore();
	if (tolower(beginAssessment)=='y') {
		reverseList(head);
		startAssessment(head);
	}

	cout << "*** Thank you for using the testing service. Goodbye! ***";


}

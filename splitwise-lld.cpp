#include <bits/stdc++.h>
using namespace std;

int cnt = 1;

class User {
public:
	string name, email, userId;
	double balance = 0.0;
	User(string name, string email) {
		this->name = name;
		this->email = email;
		this->userId = name;
	}
};

enum ShareType {
	PAID = 'PAID', BORROWED = 'BORROWED'
};

class Share {
public:
	string userId;
	double amount;
	string type;
	Share(string userId, double amount, string type) {
		this->userId = userId;
		this->amount = amount;
		this->type = type;
	}
};

class Expense {
public:
	string userPaid, date, title, description;
	double amount;
	vector<Share> individualShares;
	Expense(){}
	Expense(
		string payeeUserId, 
		double amountPaid,
		vector<Share> shares
	) {
		userPaid = payeeUserId;
		date = "12-10-2021";
		title = payeeUserId + "-paid";
		amount = amountPaid;
		description = "random description";
		individualShares = shares;
	}
};

class LedgerStatement {
public:
	string payeeUserId, beneficiaryUserId;
	double amount;
	LedgerStatement(string payeeUserId, string beneficiaryUserId, double amount) {
		this->payeeUserId = payeeUserId;
		this->beneficiaryUserId = beneficiaryUserId;
		this->amount = amount;
	}
};

class Ledger {
public:
	vector<LedgerStatement> statements;
	vector<LedgerStatement> getLedger(string userId) {
		if(userId != "") {
			vector<LedgerStatement> filteredLedger;
			for(auto statement : this->statements) {
				if(statement.payeeUserId == userId or statement.beneficiaryUserId == userId)
					filteredLedger.push_back(statement);
			}
			return filteredLedger;
		}
		return this->statements;
	}
	unordered_map<string, double> getUserAmountMap(Expense latestExpense) {
		unordered_map<string, double> userAmountMap;
		
		for(auto statement : this->statements) {
			userAmountMap[statement.payeeUserId] -= statement.amount;
			userAmountMap[statement.beneficiaryUserId] += statement.amount;
		}
		for(auto share : latestExpense.individualShares) {
			userAmountMap[share.userId] += share.type == "PAID" ? share.amount : -1*share.amount;
		}
		// printit(userAmountMap);
		return userAmountMap;
	}
	
	vector<LedgerStatement> getPayeeBeneficiaryMap(unordered_map<string, double> userAmountMap) {
		vector<pair<string, double>> whoGets;
		vector<LedgerStatement> statements;
		for(auto itr : userAmountMap) {
			if(itr.second > 0) {
				whoGets.push_back({itr.first, itr.second});
			}
		}

		int idxUptoPaid = 0;

		for(auto itr: userAmountMap) {
			if(itr.second > 0) continue;
			double amountTobePaid = abs(itr.second);
			string payeeUserId = itr.first;
			while(amountTobePaid > 0 and idxUptoPaid < whoGets.size()) {
				if(amountTobePaid >= whoGets[idxUptoPaid].second) {
					statements.push_back(
						LedgerStatement(
							payeeUserId,
							whoGets[idxUptoPaid].first, 
							whoGets[idxUptoPaid].second
						)
					);
					whoGets[idxUptoPaid++].second = 0;
				}else{
					statements.push_back(
						LedgerStatement(
							payeeUserId,
							whoGets[idxUptoPaid].first, 
							amountTobePaid
						)
					);
					whoGets[idxUptoPaid].second -= amountTobePaid;
					amountTobePaid = 0;
				}
			}
		}

		return statements;
	}

	vector<LedgerStatement> createLedgerStatments(unordered_map<string, double> userAmountMap) {
		vector<LedgerStatement> statements = getPayeeBeneficiaryMap(userAmountMap);
		return statements;
	}

	void update(Expense latestExpense) {
		unordered_map<string, double> userAmountMap = getUserAmountMap(latestExpense);
		this->statements = createLedgerStatments(userAmountMap);
		return;
	}

	void print(string userId) {
		vector<LedgerStatement> statementsToPrint = getLedger(userId);
		cout << "Printing ledger . . .\n";
		if(!statementsToPrint.size()) {
			cout << "Nothing found\n\n";
			return;
		}
		for(auto statement : statementsToPrint) {
			cout << statement.payeeUserId << " owes " << statement.beneficiaryUserId << ": " << abs(statement.amount) << endl;
		}
		cout << endl;
	}
};

class ExpenseApp {
	string id, name;
	vector<User> members;
	Ledger ledger;
public:
	vector<Expense> expenses;
	ExpenseApp(string name, vector<User> users) {
		this->name = name;
		this->id = name + ":random-number-here";
		members = users;
	}
	void showBalance(string userId = "") {
		ledger.print(userId);
	}

	void addExpense(Expense expense) {
		ledger.update(expense);
		this->expenses.push_back(expense);
		return;
	}
};

class EqualShareExpense : public Expense {
public:
	EqualShareExpense(
		string payeeUserId, 
		double amountPaid,
		vector<Share> shares
	) {
		this->userPaid = payeeUserId;
		this->date = "12-10-2021";
		this->title = payeeUserId + "paid";
		this->amount = amountPaid;
		this->description = "random description";
		this->individualShares = shares;
	}
		
};

class ExactShareExpense : public Expense {
public:
	ExactShareExpense(
		string payeeUserId, 
		double amountPaid,
		vector<Share> shares
	) {
		this->userPaid = payeeUserId;
		this->date = "12-10-2021";
		this->title = payeeUserId + "paid";
		this->amount = amountPaid;
		this->description = "random description";
		this->individualShares = shares;
	}
		
	bool validateShare() {
		double sumOfShares = 0;
		for (const auto share : this->individualShares) {
			sumOfShares += share.type == "PAID" ? -share.amount : share.amount;
		}
		return sumOfShares == 0;
	}
};

Expense expenseSplitService(
	string payeeUserId,
	double amountPaid,
	string expenseType,
	vector<string> borrowingUserIds,
	vector<double> borrowedAmount = {}
) {
	int usersCount = borrowingUserIds.size();
	vector<Share> shares;
	int temp = amountPaid;

	if(expenseType == "EQUAL") {
		double eachShareAmount = amountPaid / usersCount;
		for(string userId : borrowingUserIds) {
			if(userId != payeeUserId) 
				shares.push_back(Share(userId, eachShareAmount, "BORROWED"));
		}
		shares.push_back(Share(payeeUserId, amountPaid - eachShareAmount, "PAID"));
		return EqualShareExpense(payeeUserId, amountPaid, shares);
	}else if(expenseType == "EXACT") {
		for(int idx; idx < usersCount; ++idx) {
			if(borrowingUserIds[idx] == payeeUserId){
				temp -= borrowedAmount[idx];
				continue;
			}
			shares.push_back(Share(borrowingUserIds[idx], borrowedAmount[idx], "BORROWED"));
		}
		shares.push_back(Share(payeeUserId, temp, "PAID"));
		ExactShareExpense expenseToReturn(payeeUserId, amountPaid, shares);
		if(!expenseToReturn.validateShare())
			throw std::invalid_argument("Exact shares don't sum upto the totalAmount.");
		return expenseToReturn;
	}
}

int main() {
	vector<User> users;
	users.push_back(
		User("ankit", "ankit@exp.com")
	);
	users.push_back(
		User("prachi", "prachi@exp.com")
	);
	users.push_back(
		User("abhishek", "abhishek@exp.com")
	);
	users.push_back(
		User("pankaj", "pankaj@exp.com")
	);

	ExpenseApp goa("goaaa", users);
	goa.showBalance();
	goa.showBalance("prachi");

	Expense tickets = expenseSplitService(
		"ankit",
		9999.0,
		"EQUAL",
		{"ankit", "prachi", "pankaj"}
	);
	goa.addExpense(tickets);
	goa.showBalance();
	goa.showBalance("prachi");

	Expense food = expenseSplitService(
		"prachi",
		6000.0,
		"EQUAL",
		{"ankit", "prachi", "pankaj"}
	);
	goa.addExpense(food);
	goa.showBalance();
	goa.showBalance("prachi");

	Expense squba = expenseSplitService(
		"pankaj",
		3000.0,
		"EXACT",
		{"prachi", "pankaj"},
		{1500, 1500}
	);
	goa.addExpense(squba);
	goa.showBalance();
	goa.showBalance("prachi");

}

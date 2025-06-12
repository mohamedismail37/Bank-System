# 🏦 C++ Bank System

A fully functional, file-based banking system built in C++. It supports user authentication, permission-based access (Admin and User), and core banking operations like deposit, withdrawal, transfer, and transaction tracking.

---

## 🚀 Features

- 🔐 **Login System**
  - Separate roles: `Admin` and `User`

- 💳 **Banking Operations**
  - Deposit, Withdraw, and Transfer
  - Transaction validation and balance checking

- 🔑 **Admin Controls**
  - View all users
  - Reset passwords
  - Delete or create accounts

- 🗃️ **Data Handling**
  - All data is stored using plain text files

---

## 🛠️ Technologies Used

- **Language**: C++
- **Data Storage**: File Handling (`.txt` files)

---
## 🌳 System Structure
                            Login----------------------------------------------------------------------------------------<
                              |                                                                                          |
                          Main Menu                                                                                      |
         -----------------------------------------------------------------------------------------------------------     |
         |         |        |          |        |            |                                   |                 |     |
    Show C List  AddC    DeleteC   UpdateC    FindC    Transaction Menu                     Manage Users        Logout---^
                                                       /     |       \                           |
                                               Deposit    Withdraw   Total Balances              |-List Users
                                                                                                 |-Add User
                                                                                                 |-Delete User
                                                                                                 |-Update User
                                                                                                 |-Find User
   

    *) C = Client


---

## 📷 Screenshots
<details>
  <summary>📸 Click to view screenshots</summary>

  ### 🔐 Login Page  
  ![Login Screenshot](assets/screenshots/Login/Login.png)

  ---

  ### 🏠 Main Menu  
  ![Main Menu](assets/screenshots/MainMenu/MainMenu.png)

  #### ➕ Add New Client  
  ![Add Client](assets/screenshots/MainMenu/AddNewClient.png)

  #### 🔍 Find Client  
  ![Find Client](assets/screenshots/MainMenu/FindClient.png)

  #### ✏️ Update Client  
  ![Update Client](assets/screenshots/MainMenu/UpdateClient.png)

  #### 🗑️ Delete Client  
  ![Delete Client](assets/screenshots/MainMenu/DeleteClient.png)

  #### 📋 List All Clients  
  ![List Clients](assets/screenshots/MainMenu/ShowClientList.png)

---

  ### 🧾 Transaction Menu  
  ![Transaction Menu](assets/screenshots/TransactionMenu/TransactionMenu.png)

  ### 💰 Deposit Page  
  ![Deposit Page](assets/screenshots/TransactionMenu/Transactions_DepositScreen.png)

  ### 💸 Withdraw Page  
  ![Withdraw Page](assets/screenshots/TransactionMenu/Transactions_WithdrawScreen.png)

  ### ⚖️ Total Balances  
  ![Transfer Screen](assets/screenshots/TransactionMenu/TotalBalances.png)

---

  ### 🛠️ Manage Users Menu  
  ![Manage Users Menu](assets/screenshots/ManageUsersMenu/ManageUsersScreen.png)

  #### ➕ Add New User  
  ![Add User](assets/screenshots/ManageUsersMenu/AddingUser.png)

  #### ✏️ Update User  
  ![Update User](assets/screenshots/ManageUsersMenu/UpdateUser.png)

  #### 📋 List All Users  
  ![List Users](assets/screenshots/ManageUsersMenu/UsersList.png)

</details>





                          

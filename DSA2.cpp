#!/usr/bin/env python
# coding: utf-8

class HashTable:
    def __init__(self, size):
        self.size = size
        self.table = [[] for _ in range(size)]

    def hash_function(self, key):
        return key % self.size

    def insert(self, key, value):
        index = self.hash_function(key)
        chain = self.table[index]
        for i, (k, v) in enumerate(chain):
            if k == key:
                chain[i] = (key, value)
                return
        chain.insert(0, (key, value))

    def search(self, key):
        index = self.hash_function(key)
        chain = self.table[index]
        for k, v in chain:
            if k == key:
                return v
        return None

    def delete(self, key):
        index = self.hash_function(key)
        chain = self.table[index]
        for i, (k, v) in enumerate(chain):
            if k == key:
                del chain[i]
                return True
        return False

    def display(self):
        for i, chain in enumerate(self.table):
            print(f"Bucket {i}: {chain}")

def display_menu():
    print("\nMenu:")
    print("1. Insert key-value pair")
    print("2. Search for a key")
    print("3. Delete a key")
    print("4. Display the hash table")
    print("5. Exit")

def user_input():
    size = int(input("Enter the size of the hash table: "))
    ht = HashTable(size=size)
    while True:
        display_menu()
        choice = input("Enter your choice (1/2/3/4/5): ").strip()
        if choice == '1':
            key = int(input("Enter key to insert: "))
            value = input("Enter value to insert: ")
            ht.insert(key, value)
            print(f"Inserted ({key}, {value}) into the hash table.")
        elif choice == '2':
            key = int(input("Enter key to search for: "))
            result = ht.search(key)
            if result is not None:
                print(f"Value for key {key}: {result}")
            else:
                print(f"Key {key} not found.")
        elif choice == '3':
            key = int(input("Enter key to delete: "))
            if ht.delete(key):
                print(f"Key {key} deleted.")
            else:
                print(f"Key {key} not found.")
        elif choice == '4':
            print("\nHash Table Content:")
            ht.display()
        elif choice == '5':
            print("Exiting the program.")
            break
        else:
            print("Invalid choice! Please enter a valid option (1/2/3/4/5).")

if __name__ == "__main__":
    user_input()

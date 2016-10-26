set serveroutput on;
execute DBMS_OUTPUT.PUT_LINE('new user_id: ' || tamagotchi.createUser('Vika', 3456577));

---execute tamagotchi.printUsersAmount;
execute tamagotchi.deleteUser(3);
---execute tamagotchi.printUsersAmount;
set serveroutput on;

execute DBMS_OUTPUT.PUT_LINE('new user_id: ' || tamagotchi.createUser('Vika', 3456577));
execute DBMS_OUTPUT.PUT_LINE('new user_id: ' || tamagotchi.createUser('Sasha', 4557733));

execute tamagotchi.printUsersAmount;
execute tamagotchi.deleteUser(1);
execute tamagotchi.printUsersAmount;

execute DBMS_OUTPUT.PUT_LINE('user_id (update name): ' || tamagotchi.updateUserName(1, 'Cygni'));

-- Potentially doesn't work
execute DBMS_OUTPUT.PUT_LINE('new pet_id: ' || tamagotchi.addPetToUser(2, 1, 'Pushok'));

  ---  procedure readUserById(u_id number);
execute tamagotchi.readUserById(2);
execute tamagotchi.readUserPetByUserId(9);
execute DBMS_OUTPUT.PUT_LINE('add 50 money: ' || tamagotchi.addMoneyToUser(1, 50));

execute DBMS_OUTPUT.PUT_LINE('testing health_condition');
DECLARE
    result HEALTH_CONDITION;
BEGIN
    select state into result from pets where (rownum = 1);
    dbms_output.put_line('is Healthy? ' || result.isHealthy());
END;
/

--- Продумать:
--- 0) Возраст животного -> сделано
--- 1) Болезни -> стали чистотой
--- 2) Обновление состояний -> процесс, запускающийся по расписанию
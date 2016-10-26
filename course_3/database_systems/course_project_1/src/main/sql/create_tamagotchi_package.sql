create or replace package tamagotchi as
  function createUser(u_id number, name varchar(255), phone number) return number;
  procedure deleteUser(u_id number);

  function updateUserName(u_id number, name varchar(255)) return number;
  function addPetToUser(u_id number, petName varchar(255), petTextureId number) return number;
  function addUserPhoto(u_id number, path_to_photo varchar(255)) return number;
  function addMoneyToUser(u_id number, moneyAmount number) return number;
  procedure readUserById(u_id number);
  procedure readUserPetByUserId(u_id number);
end util;
/

create or replace package body tamagotchi as
  function createUser(u_id number, name varchar(255), phone number) return number is
    result users.id%type;
  begin
    ---select salary into result from salaries where h_id = human_id;
    return 0;
  exception
    when NO_DATA_FOUND then
    return NULL;
  end;

  procedure deleteUser(u_id number) as
  begin
    delete from users where id = u_id;
  end;
end util;
/
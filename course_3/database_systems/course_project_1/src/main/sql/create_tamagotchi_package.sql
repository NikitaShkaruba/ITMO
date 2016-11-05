create or replace package tamagotchi as
  function createUser(user_name varchar2, phone number) return number;
  procedure printUsersAmount;
  procedure deleteUser(u_id number);

  function updateUserName(u_id number, user_name varchar2) return number;
  function addPetToUser(u_id number, a_id number, petName varchar2) return number;
  function addMoneyToUser(u_id number, moneyAmount number) return number;
  procedure readUserById(u_id number);
  procedure readUserPetByUserId(u_id number);
end tamagotchi;
/

create or replace package body tamagotchi as
  function createUser(user_name varchar2, phone number) return number is
    result users.id%type;
  begin
    ---select salary into result from salaries where h_id = human_eid;
    insert into users values(0, user_name, NULL, NULL, 50, phone) returning id into result;
    return result;
  exception
    when NO_DATA_FOUND then
    return NULL;
  end;

  procedure deleteUser(u_id number) as
  begin
    delete from users where id = u_id;
  end;

function updateUserName(u_id number, user_name varchar2) return number is
    result users.id%type;
  begin
    ---select salary into result from salaries where h_id = human_id;
    UPDATE users
	   SET name = user_name
	   WHERE id = u_id returning id into result;
    return result;
  exception
    when NO_DATA_FOUND then
    return NULL;
  end;

  ---function addPetToUser(u_id number, petName varchar(255), petTextureId number) return number;
  function addPetToUser(u_id number, a_id number, petName varchar2) return number is
    result users.id%type;
   begin
    insert into pets values(0, petName, a_id, u_id, NULL, NULL) returning id into result;
    return result;
  exception
    when NO_DATA_FOUND then
    return NULL;
  end;

  function addMoneyToUser(u_id number, moneyAmount number)  return number is
      result users.money_amount%type;
    begin
          UPDATE users
      	   SET money_amount = money_amount + moneyAmount
      	   WHERE id = u_id returning money_amount into result;
      return result;
    exception
      when NO_DATA_FOUND then
      return NULL;
    end;

  ---  procedure readUserById(u_id number);
    procedure readUserById(u_id number) as result users.name%type;
  begin
    select name into result from users where id = u_id;
    DBMS_OUTPUT.PUT_LINE('read User By Id: ' || result);
  end;

  ---procedure readUserPetByUserId(u_id number);
    procedure readUserPetByUserId(u_id number) as result pets.name%type;
  begin
    select name into result from pets where id = (select pet_id from users where id = u_id);
    DBMS_OUTPUT.PUT_LINE('read User Pet By User Id: ' || result);
  end;
 --- insert into users values(9, 'Tuck', 1, NULL, 0, 9997755);

  procedure printUsersAmount as
    users_amount number;
  begin
    select count(*) into users_amount from users;
    DBMS_OUTPUT.PUT_LINE('users amount: ' || users_amount);
  end;
end tamagotchi;
/








--- Script to create all the tables and relations between them
--- Todo: Add triggers for automatic Id generation

create table textures(
    id number constraint textures_pk primary key not null,
    texture blob
);

create table cosmetics (
    id number constraint cosmetics_pk primary key not null,
    name varchar(255) not null,
    type varchar(255) not null,
    priсe number not null
);

create table food (
    id number constraint food_pk primary key not null,
    name varchar(255)  not null,
    satiety number not null
);

create table entertainments(
    id number constraint entertainments_pk primary key not null,
    name varchar(255)  not null,
    quality number
);

create table sceneries (
    id number constraint sceneries_pk primary key not null,
    name varchar(255) not null,
    texture blob
);

create table photos (
    id number constraint photos_pk primary key not null,
    data blob
);

create table animals (
    id number constraint animals_pk primary key not null,
    name varchar(255)  not null,
    texture_id number not null,
    CONSTRAINT animals_fk FOREIGN KEY (texture_id) REFERENCES textures(id)
);

CREATE UNIQUE INDEX i_animals_texture_id ON animals(texture_id);

create TYPE health_condition as OBJECT (
    happiness number,
    hungriness number,
    cleanliness number,
    --- returns 0 if ill, 1 if healthy
    MAP MEMBER FUNCTION isHealthy RETURN NUMBER
);
/

CREATE TYPE BODY health_condition AS
    MAP MEMBER FUNCTION isHealthy RETURN NUMBER IS
    BEGIN
        if happiness < 2 then
            return 0;
        end if;

        if hungriness > 9 then
            return 0;
        end if;

        if cleanliness < 2 then
            return 0;
        end if;

        return 1;
    END;
END;
/

--- Egg, Baby, Child, Teenager, Adult, Senior
create table age_types (
    id number constraint age_types_pk primary key not null,
    name varchar(255)
);

create table pets (
    id number constraint pets_pk primary key not null,
    name varchar(255),
    animal_id number not null,
    CONSTRAINT pets_fk FOREIGN KEY (animal_id) REFERENCES animals(id),
    user_id number not null,
    birth_date date,
    death_date date,
    age_type_id number not null,
    CONSTRAINT pets_fk3 FOREIGN KEY (age_type_id) REFERENCES age_types(id),
    state health_condition
);

CREATE INDEX i_pets_animal_id ON pets(animal_id);

create table users (
    id number constraint users_pk primary key not null,
    name varchar(255)  not null,
    pet_id number,
    photo_id number,
    money_amount number,
    phone number(11),
    CONSTRAINT users_fk FOREIGN KEY (pet_id) REFERENCES pets(id),
    CONSTRAINT users_fk2 FOREIGN KEY (photo_id) REFERENCES photos(id)
);

CREATE UNIQUE INDEX i_users_pet_id_photo_id ON users(pet_id, photo_id);

ALTER TABLE pets ADD FOREIGN KEY (user_id) REFERENCES users(id);

CREATE INDEX i_pets_user_id ON pets(user_id);

create table ratings (
    id number constraint rating_pk primary key not null,
    user_id number not null,
    CONSTRAINT rating_fk FOREIGN KEY (user_id) REFERENCES users(id)
);

CREATE UNIQUE INDEX i_ratings_user_id ON ratings(user_id);

create table user_cosmetics (
    user_id number not null,
    cosmetic_id number not null,
    CONSTRAINT user_cosmetic_fk FOREIGN KEY (user_id) REFERENCES users(id),
    CONSTRAINT user_cosmetic_fk2 FOREIGN KEY (cosmetic_id) REFERENCES cosmetics(id)
);

CREATE UNIQUE INDEX i_user_cosmetics_uid_cosmid ON user_cosmetics(user_id, cosmetic_id);

create table friends(
    from_id number not null,
    to_id number not null,
    CONSTRAINT friends_fk FOREIGN KEY (from_id) REFERENCES users(id),
    CONSTRAINT friends_fk2 FOREIGN KEY (to_id) REFERENCES users(id)
);

CREATE UNIQUE INDEX i_friends_fromid_toid ON friends(from_id, to_id);

--------------------- Insert triggers and sequences for them ---------------------

--- textures
create sequence textures_id_seq increment by 1 start with 1;

create or replace trigger textures_insert
before insert on textures for each row
begin
    select textures_id_seq.nextval into :new.id from dual;
end;
/

--- cosmetics
create sequence cosmetics_id_seq increment by 1 start with 1;

create or replace trigger cosmetics_insert
before insert on cosmetics for each row
begin
    select cosmetics_id_seq.nextval into :new.id from dual;
end;
/

--- food
create sequence food_id_seq increment by 1 start with 1;

create or replace trigger food_insert
before insert on food for each row
begin
    select food_id_seq.nextval into :new.id from dual;
end;
/

--- entertainments
create sequence entertainments_id_seq increment by 1 start with 1;

create or replace trigger entertainments_insert
before insert on entertainments for each row
begin
    select entertainments_id_seq.nextval into :new.id from dual;
end;
/

--- sceneries
create sequence sceneries_id_seq increment by 1 start with 1;

create or replace trigger sceneries_insert
before insert on sceneries for each row
begin
    select sceneries_id_seq.nextval into :new.id from dual;
end;
/

--- photos
create sequence photos_id_seq increment by 1 start with 1;

create or replace trigger photos_insert
before insert on photos for each row
begin
    select photos_id_seq.nextval into :new.id from dual;
end;
/

--- age_types
create sequence age_types_id_seq increment by 1 start with 1;

create or replace trigger age_types_insert
before insert on age_types for each row
begin
    select age_types_id_seq.nextval into :new.id from dual;
end;
/

--- pets
create sequence pets_id_seq increment by 1 start with 1;

create or replace trigger pets_insert
before insert on pets for each row
begin
    select pets_id_seq.nextval into :new.id from dual;
end;
/

--- animals
create sequence animals_id_seq increment by 1 start with 1;

create or replace trigger animals_insert
before insert on animals for each row
begin
    select animals_id_seq.nextval into :new.id from dual;
end;
/

--- users
create sequence users_id_seq increment by 1 start with 1;

create or replace trigger users_insert
before insert on users for each row
begin
    select users_id_seq.nextval into :new.id from dual;
end;
/

--- ratings
create sequence ratings_id_seq increment by 1 start with 1;

create or replace trigger ratings_insert
before insert on ratings for each row
begin
    select ratings_id_seq.nextval into :new.id from dual;
end;
/

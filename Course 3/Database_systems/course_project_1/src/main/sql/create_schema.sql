--- Script to create all the tables and relations between them
--- Todo: Add triggers for automatic Id generation

create table textures(
    id number constraint textures_pk primary key not null,
    texture blob
);

create table cosmetics (
    id number constraint cosmetics_pk primary key not null,
    name varchar(255)  not null,
    type varchar(255)  not null,
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

create table user_photoes (
    id number constraint user_photoes_pk primary key not null,
    data blob
);

create table pets (
    id number constraint pets_pk primary key not null,
    name varchar(255),
    animal_id number not null,
    CONSTRAINT pets_fk FOREIGN KEY (animal_id) REFERENCES animals(id),
    user_id number not null,
    death_date date, 
    happiness number,
    hungriness number,
    health number    
);

create table animals (
    id number constraint animals_pk primary key not null,
    name varchar(255)  not null,
    texture_id number not null,
    CONSTRAINT animals_fk FOREIGN KEY (texture_id) REFERENCES textures(id)
);

create table users (
    id number constraint users_pk primary key not null,
    name varchar(255)  not null,
    pet_id number,
    photo_id number not null,
    money_amount number,
    phone number(11),
    CONSTRAINT users_fk FOREIGN KEY (pet_id) REFERENCES pets(id),
    CONSTRAINT users_fk2 FOREIGN KEY (photo_id) REFERENCES user_photoes(id)
);

ALTER TABLE pets ADD FOREIGN KEY (user_id) REFERENCES users(id);

create table ratings (
    id number constraint rating_pk primary key not null,
    user_id number not null,
    rank number,
    CONSTRAINT rating_fk FOREIGN KEY (user_id) REFERENCES users(id)
);

create table user_cosmetics (
    user_id number not null,
    cosmetic_id number not null,
    CONSTRAINT user_cosmetic_fk FOREIGN KEY (user_id) REFERENCES users(id),
    CONSTRAINT user_cosmetic_fk2 FOREIGN KEY (cosmetic_id) REFERENCES cosmetics(id)
);

create table friends(
    from_id number not null,
    to_id number not null,
    CONSTRAINT friends_fk FOREIGN KEY (from_id) REFERENCES users(id),
    CONSTRAINT friends_fk2 FOREIGN KEY (to_id) REFERENCES users(id)
);

create table admin_users (
    user_id number,
    CONSTRAINT admin_users_fk FOREIGN KEY (user_id) REFERENCES users(id)
);

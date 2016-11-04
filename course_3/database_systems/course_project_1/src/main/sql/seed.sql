--- Todo: understand how to insert blobs
insert into food values(0, 'Borch', 10);
insert into food values(0, 'Okroshka', 8);

insert into entertainments values(0, 'play guitar', 4);
insert into entertainments values(0, 'play computer', 9);
insert into entertainments values(0, 'do sports', 8);

insert into cosmetics values(0, 'cat ears', 'head', 300);
insert into cosmetics values(0, 'kowboy hat', 'head', 250);
insert into cosmetics values(0, 'ring with diamond', 'hands', 50);

insert into sceneries values(0, 'waterfall', utl_raw.cast_to_raw('waterfall.png'));
insert into sceneries values(0, 'cozy_chair', utl_raw.cast_to_raw('cozy_chair.png'));

insert into user_photoes values(0, utl_raw.cast_to_raw('my_ava.png'));
insert into user_photoes values(0, utl_raw.cast_to_raw('fabulous_nikita.png'));

insert into users values(0, 'Nikita', NULL, NULL, 0, 9819584408);
insert into users values(0, 'Victoria', NULL, NULL, 0, 9112489674);

insert into textures values(0, utl_raw.cast_to_raw('cat_texture.png'));
insert into textures values(0, utl_raw.cast_to_raw('chupokabra_texture.png'));

insert into animals values(0, 'Cat', 1);
insert into animals values(0, 'Chupokabra', 2);

insert into pets values(0, 'Fluffy', 1, 1, TO_DATE('17-05-2017', 'dd-mm-yyyy'), health_condition(3, 4, 2));
insert into pets values(0, 'Smokey', 2, 2, TO_DATE('17-05-2017', 'dd-mm-yyyy'), health_condition(3, 4, 2));

insert into admin_users values(1);
insert into admin_users values(2);

insert into friends values(1, 2);
insert into friends values(2, 1);

insert into ratings values(0, 1, 1);
insert into ratings values(0, 2, 2);

insert into user_cosmetics values(1, 1);
insert into user_cosmetics values(1, 2);

package itmo.dbs.models.repositories;

import itmo.dbs.models.UserPhoto;
import org.springframework.data.repository.CrudRepository;
import org.springframework.data.rest.core.annotation.RepositoryRestResource;

@RepositoryRestResource(collectionResourceRel = "user_photos", path = "user_photos")
public interface UserPhotosRepository extends CrudRepository<UserPhoto, Long> {}

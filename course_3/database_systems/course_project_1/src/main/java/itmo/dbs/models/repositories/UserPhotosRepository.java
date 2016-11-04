package itmo.dbs.models.repositories;

import itmo.dbs.models.UserPhoto;
import org.springframework.data.repository.CrudRepository;
import org.springframework.data.rest.core.annotation.RepositoryRestResource;

@RepositoryRestResource
public interface UserPhotosRepository extends CrudRepository<UserPhoto, Long> {}

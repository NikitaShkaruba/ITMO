package itmo.dbs.models.repositories;

import itmo.dbs.models.Photo;
import org.springframework.data.repository.CrudRepository;
import org.springframework.data.rest.core.annotation.RepositoryRestResource;

@RepositoryRestResource
public interface PhotosRepository extends CrudRepository<Photo, Long> {}

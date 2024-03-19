package fact.it.mvc.RewardMusicList;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface RewardMusicListRepository extends JpaRepository<RewardMusicList, Integer> {
    // You can add custom query methods here if needed
}
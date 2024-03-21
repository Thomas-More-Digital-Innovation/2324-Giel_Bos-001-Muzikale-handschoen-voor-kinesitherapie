package fact.it.mvc.RewardMusicList;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import java.util.List;

@Service
public class RewardMusicListService {
    @Autowired
    private final RewardMusicListRepository rewardMusicListRepository;

    public RewardMusicListService(RewardMusicListRepository rewardMusicListRepository) {
        this.rewardMusicListRepository = rewardMusicListRepository;
    }

    public List<RewardMusicList> getAllRewardMusicLists() {
        return rewardMusicListRepository.findAll();
    }

    public RewardMusicList getRewardMusicListById(int id) {
        return rewardMusicListRepository.findById(id).orElse(null);
    }

    public RewardMusicList saveRewardMusicList(RewardMusicList rewardMusicList) {
        return rewardMusicListRepository.save(rewardMusicList);
    }

    public void deleteRewardMusicListById(int id) {
        rewardMusicListRepository.deleteById(id);
    }

    public List<RewardMusicList> getRewardMusicListsByRwMID(int rwMID) {
        return rewardMusicListRepository.findByRwMID(rwMID);
    }
    // You can add more service methods as per your application requirements
}

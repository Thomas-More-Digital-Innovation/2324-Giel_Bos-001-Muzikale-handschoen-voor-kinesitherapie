package fact.it.mvc.RewardLEDRing;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.stereotype.Component;

import java.util.Random;

@Component
public class RewardLedRingData implements CommandLineRunner {

    private final RewardLEDRingRepository rewardLEDRingRepository;

    @Autowired
    public RewardLedRingData(RewardLEDRingRepository rewardLEDRingRepository) {
        this.rewardLEDRingRepository = rewardLEDRingRepository;
    }

    @Override
    public void run(String... args) throws Exception {
        if (rewardLEDRingRepository.count() == 0) {
            Random random = new Random();
            for (int i = 0; i < 10; i++) {
                RewardLEDRing rewardLEDRing = new RewardLEDRing();
                rewardLEDRing.setHexCode0(generateRandomHexCode(random));
                rewardLEDRing.setHexCode1(generateRandomHexCode(random));
                rewardLEDRing.setHexCode2(generateRandomHexCode(random));
                rewardLEDRing.setHexCode3(generateRandomHexCode(random));
                rewardLEDRing.setHexCode4(generateRandomHexCode(random));
                rewardLEDRing.setHexCode5(generateRandomHexCode(random));
                rewardLEDRing.setHexCode6(generateRandomHexCode(random));
                rewardLEDRing.setHexCode7(generateRandomHexCode(random));
                rewardLEDRing.setHexCode8(generateRandomHexCode(random));
                rewardLEDRing.setHexCode9(generateRandomHexCode(random));
                rewardLEDRing.setHexCode10(generateRandomHexCode(random));
                rewardLEDRing.setHexCode11(generateRandomHexCode(random));
                rewardLEDRingRepository.save(rewardLEDRing);
            }
        }
    }

    private String generateRandomHexCode(Random random) {
        return String.format("#%02X%02X%02X", random.nextInt(256), random.nextInt(256), random.nextInt(256));
    }
}
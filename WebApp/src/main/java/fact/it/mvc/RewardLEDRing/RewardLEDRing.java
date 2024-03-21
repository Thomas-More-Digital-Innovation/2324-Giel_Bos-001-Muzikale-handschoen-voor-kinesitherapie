package fact.it.mvc.RewardLEDRing;

import javax.persistence.Entity;
import javax.persistence.Table;
import javax.persistence.Id;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Column;
import lombok.Data;

@Entity
@Data
@Table(name = "RewardLEDRing")
public class RewardLEDRing {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "rwLEDRingID")
    private int rwLEDRingID;

    @Column(name = "hexCode0")
    private String hexCode0;

    @Column(name = "hexCode1")
    private String hexCode1;

    @Column(name = "hexCode2")
    private String hexCode2;

    @Column(name = "hexCode3")
    private String hexCode3;

    @Column(name = "hexCode4")
    private String hexCode4;

    @Column(name = "hexCode5")
    private String hexCode5;

    @Column(name = "hexCode6")
    private String hexCode6;

    @Column(name = "hexCode7")
    private String hexCode7;

    @Column(name = "hexCode8")
    private String hexCode8;

    @Column(name = "hexCode9")
    private String hexCode9;

    @Column(name = "hexCode10")
    private String hexCode10;

    @Column(name = "hexCode11")
    private String hexCode11;
}

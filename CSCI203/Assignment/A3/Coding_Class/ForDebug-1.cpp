#include <iostream>
#include <vector>
#include <random>
using namespace std;

string issueName(int i);

class Issue {
    public:
        string name;
        double significance, approach;

        Issue(string name, double significance, double approach);
};

class PartyMember {
    public:
        double popularity;
        vector<Issue> stances;

        PartyMember(double popularity);
};

class Leader : public PartyMember {
    public:
        double reputation;

        Leader(double popularity, double reputation);
};

class Candidate : public PartyMember {
    public:
        double skill;

        Candidate(double popularity, double skill);
};

class CampaignTeam {
    public:
        double efficiency;

        CampaignTeam(double efficiency);
};

class PoliticalParty {
    public:
        string name;
        Leader leader;
        vector<Candidate> candidates;
        CampaignTeam campaignTeam;

        PoliticalParty(string name, Leader leader, vector<Candidate> candidates, CampaignTeam campaignTeam);
};

class ElectoralDivision {
    public:
        int number;
        vector<Issue> stances;

        ElectoralDivision(int number);
};

class DebateEvent {
    public:
        void event(PoliticalParty* politicalParty1, PoliticalParty* politicalParty2, PoliticalParty* politicalParty3, ElectoralDivision& division);
};

class PublicSpeakingEvent {
    public:
        void event(PoliticalParty* politicalParty1, PoliticalParty* politicalParty2, PoliticalParty* politicalParty3, ElectoralDivision& division);
};

class CommunityServiceEvent {
    public:
        void event(PoliticalParty* politicalParty1, PoliticalParty* politicalParty2, PoliticalParty* politicalParty3, ElectoralDivision& division);
};

class PolicyAnnouncementEvent {
    public:
        void event(PoliticalParty* politicalParty1, PoliticalParty* politicalParty2, PoliticalParty* politicalParty3);
};

class PressConferenceEvent {
    public:
        void event(PoliticalParty* politicalParty1, PoliticalParty* politicalParty2, PoliticalParty* politicalParty3);
};

class ProtestEvent {
    public:
        void event(ElectoralDivision& division);
};

class NewsReportEvent {
    public:
        void event(ElectoralDivision& division);
};

string issueName(int i) {
    string name;

    if (i == 0) {
        name = "Diseases";
    } else if (i == 1) {
        name = "Deforestation";
    } else if (i == 2) {
        name = "Climate change";
    } else if (i == 3) {
        name = "Water contamination";
    } else {
        name = "Poverty";
    }

    return name;
}

Issue::Issue(string name, double significance, double approach) : name(name), significance(significance), approach(approach) {}

PartyMember::PartyMember(double popularity) : popularity(popularity) {};

Leader::Leader(double popularity, double reputation) : PartyMember(popularity), reputation(reputation) {};

Candidate::Candidate(double popularity, double skill) : PartyMember(popularity), skill(skill) {};

CampaignTeam::CampaignTeam(double efficiency) : efficiency(efficiency) {};

PoliticalParty::PoliticalParty(string name, Leader leader, vector<Candidate> candidates, CampaignTeam campaignTeam) : name(name), leader(leader), candidates(candidates), campaignTeam(campaignTeam) {
    random_device rd;
    mt19937 gen(rd());

    for (int i = 0; i < 5; i++) { // There are 5 issues
        uniform_real_distribution<> disUpper(50.0, 100.0);
        uniform_real_distribution<> disLower(0.0, 50.0);

        double significanceRangeUpper = disUpper(gen);
        double approachRangeUpper = disUpper(gen);

        double significanceRangeLower = disLower(gen);
        double approachRangeLower = disLower(gen);

        uniform_real_distribution<> disSignificance(significanceRangeLower, significanceRangeUpper);
        uniform_real_distribution<> disApproach(approachRangeLower, approachRangeUpper);

        double significance = disSignificance(gen);
        double approach = disApproach(gen);

        this->leader.stances.push_back(Issue(issueName(i), significance, approach));

        for (Candidate& candidate : this->candidates) {
            candidate.stances.push_back(Issue(issueName(i), significance, approach));
        }
    }
}

ElectoralDivision::ElectoralDivision(int number) : number(number) {
    random_device rd;
    mt19937 gen(rd());

    for (int i = 0; i < 5; i++) { // There are 5 issues
        uniform_real_distribution<> dis(0.0, 100.0);
        double significance = dis(gen);
        double approach = dis(gen);

        stances.push_back(Issue(issueName(i), significance, approach));
    }
}

void DebateEvent::event(PoliticalParty* politicalParty1, PoliticalParty* politicalParty2, PoliticalParty* politicalParty3, ElectoralDivision& division) {
    random_device rd;
    mt19937 gen(rd());

    double party1Points = politicalParty1->candidates[division.number - 1].skill * 2 + politicalParty1->campaignTeam.efficiency;
    double party2Points = politicalParty2->candidates[division.number - 1].skill * 2 + politicalParty2->campaignTeam.efficiency;
    double party3Points = politicalParty3->candidates[division.number - 1].skill * 2 + politicalParty3->campaignTeam.efficiency;

    uniform_real_distribution<> dis(0.0, party1Points + party2Points + party3Points);

    double winnerChance = dis(gen);

    if (winnerChance <= party1Points) {
        politicalParty1->candidates[division.number - 1].popularity += politicalParty1->candidates[division.number - 1].popularity * 0.15 + politicalParty1->campaignTeam.efficiency * 0.1;
        cout << "   Candidate of " << politicalParty1->name << " is the winner of the debate! Their popularity has increased!" << endl;
        // cout << politicalParty1.candidates[division.number - 1].popularity << endl;
    } else if (winnerChance <= party1Points + party2Points) {
        politicalParty2->candidates[division.number - 1].popularity += politicalParty2->candidates[division.number - 1].popularity * 0.15 + politicalParty2->campaignTeam.efficiency * 0.1;
        cout << "   Candidate of " << politicalParty2->name << " is the winner of the debate! Their popularity has increased!" << endl;
        // cout << politicalParty2.candidates[division.number - 1].popularity << endl;
    } else {
        politicalParty3->candidates[division.number - 1].popularity += politicalParty3->candidates[division.number - 1].popularity * 0.15 + politicalParty3->campaignTeam.efficiency * 0.1;
        cout << "   Candidate of " << politicalParty3->name << " is the winner of the debate! Their popularity has increased!" << endl;
        // cout << politicalParty3.candidates[division.number - 1].popularity << endl;
    }
}

void PublicSpeakingEvent::event(PoliticalParty* politicalParty1, PoliticalParty* politicalParty2, PoliticalParty* politicalParty3, ElectoralDivision& division) {
    
    random_device rd;
    mt19937 gen(rd());

    vector<PoliticalParty*> parties = {politicalParty1, politicalParty2, politicalParty3};

    for (int i = 0; i < parties.size(); i++) {
        uniform_real_distribution<> dis(0.0, parties[i]->candidates[division.number - 1].skill);

        double speakQuality = dis(gen);

        if (speakQuality > parties[i]->candidates[division.number - 1].skill * 0.4) {
            parties[i]->candidates[division.number - 1].popularity += parties[i]->candidates[division.number - 1].popularity * 0.2;
            cout << "   Candidate of " << parties[i]->name << " has a gorgeous speech! Their popularity has increased!" << endl;
            // cout << parties[i]->candidates[division.number - 1].popularity << endl;
        } else {
            parties[i]->candidates[division.number - 1].popularity -= parties[i]->candidates[division.number -1].popularity * 0.3;
            cout << "   Candidate of " << parties[i]->name << " has a terrible speech! Their popularity has decreased!" << endl;
            // cout << parties[i]->candidates[division.number - 1].popularity << endl;
        }
    }
}

void CommunityServiceEvent::event(PoliticalParty* politicalParty1, PoliticalParty* politicalParty2, PoliticalParty* politicalParty3, ElectoralDivision& division) {
    random_device rd;
    mt19937 gen(rd());

    vector<PoliticalParty*> parties = {politicalParty1, politicalParty2, politicalParty3};

    for (int i = 0; i < parties.size(); i++) {
        uniform_real_distribution<> dis(0.0, 1.0);

        double serviceQuality = dis(gen);

        if (serviceQuality > 0.66) {
            parties[i]->candidates[division.number - 1].popularity += parties[i]->candidates[division.number - 1].popularity * 0.25;
            cout << "   Candidate of " << parties[i]->name << " has provided excellent service quality! Their popularity has dramatically increased!" << endl;
            // cout << parties[i]->candidates[division.number - 1].popularity << endl;
        } else if (serviceQuality > 0.33) {
            parties[i]->candidates[division.number - 1].popularity += parties[i]->candidates[division.number - 1].popularity * 0.15;
            cout << "   Candidate of " << parties[i]->name << " has provided good service quality! Their popularity has increased!" << endl;
            // cout << parties[i]->candidates[division.number - 1].popularity << endl;
        } else {
            parties[i]->candidates[division.number - 1].popularity += parties[i]->candidates[division.number - 1].popularity * 0.05;
            cout << "   Candidate of " << parties[i]->name << " has provided not very good service quality! Their popularity has increased a little!" << endl;
            // cout << parties[i]->candidates[division.number - 1].popularity << endl;
        }
    }
}

void PolicyAnnouncementEvent::event(PoliticalParty* politicalParty1, PoliticalParty* politicalParty2, PoliticalParty* politicalParty3) {
    random_device rd;
    mt19937 gen(rd());

    vector<PoliticalParty*> parties = {politicalParty1, politicalParty2, politicalParty3};

    for (int i = 0; i < parties.size(); i++) {
        uniform_real_distribution<> dis(0.0, parties[i]->leader.reputation);

        double policyQuality = dis(gen);

        if (policyQuality > parties[i]->leader.reputation * 0.4) {
            parties[i]->leader.popularity += parties[i]->leader.popularity * 0.2;
            cout << "   The new policy is great! The popularity of the leader of " << parties[i]->name << " has increased!" << endl;
        } else {
            parties[i]->leader.popularity -= parties[i]->leader.popularity * 0.3;
            cout << "   The new policy is awful! The popularity of the leader of " << parties[i]->name << " has decreased!" << endl;
        }
    }
}

void PressConferenceEvent::event(PoliticalParty* politicalParty1, PoliticalParty* politicalParty2, PoliticalParty* politicalParty3) {
    random_device rd;
    mt19937 gen(rd());

    vector<PoliticalParty*> parties = {politicalParty1, politicalParty2, politicalParty3};

    for (int i = 0; i < parties.size(); i++) {
        uniform_real_distribution<> dis(0.0, parties[i]->leader.reputation);

        double conferenceSuccess = dis(gen);

        if (conferenceSuccess > parties[i]->leader.reputation * 0.75) {
            parties[i]->leader.popularity += parties[i]->leader.popularity * 0.25;
            cout << "   The conference is excellent! The popularity of the leader of " << parties[i]->name << " has dramatically increased!" << endl;
        } else if (conferenceSuccess > parties[i]->leader.reputation * 0.5) {
            parties[i]->leader.popularity += parties[i]->leader.popularity * 0.15;
            cout << "   The conference is good! The popularity of the leader of " << parties[i]->name << " has increased!" << endl;
        } else if (conferenceSuccess > parties[i]->leader.reputation * 0.25) {
            parties[i]->leader.popularity -= parties[i]->leader.popularity * 0.15;
            cout << "   The conference is awful! The popularity of the leader of " << parties[i]->name << " has decreased!" << endl;
        } else {
            parties[i]->leader.popularity -= parties[i]->leader.popularity * 0.25;
            cout << "   The conference is terrible! The popularity of the leader of " << parties[i]->name << " has dramatically decreased!" << endl;
        }
    }
}

void ProtestEvent::event(ElectoralDivision& division) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> disEvent(0, 4);
    uniform_real_distribution<> dis(0.0, 10.0);

    int eventChance = disEvent(gen);
    double protestImpact = dis(gen);

    division.stances[eventChance].significance += protestImpact;
    cout << "   There is a protest about " << division.stances[eventChance].name << "! Its significance has increased!" << endl;
}

void NewsReportEvent::event(ElectoralDivision& division) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> disEvent(0, 4);
    uniform_real_distribution<> dis(0.0, 10.0);

    int eventChance = disEvent(gen);
    double reportImpact = dis(gen);

    division.stances[eventChance].approach += reportImpact;
    cout << "   There is a report about " << division.stances[eventChance].name << "! Its approach has increased!" << endl;
}

int main() {

    int n = 3;
    int m = 1;

    if (n < 1 || n > 10 || m < 1 || m > 30) {
        cerr << "Invalid input. n should be in the range 1 to 10 inclusive. m should be in the range 1 to 30 inclusive." << endl;
        cerr << "Usage: .\\AEP n m" << endl;
        return 1;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(10.0, 40.0);

    vector<PoliticalParty*> politicalParties;
    vector<ElectoralDivision> electoralDivisions;
    
    vector<Candidate> candidates1;
    vector<Candidate> candidates2;
    vector<Candidate> candidates3;

    for (int i = 0; i < n; i++) {
        ElectoralDivision electoralDivision(i + 1);

        Candidate candidate1(dis(gen), dis(gen));
        Candidate candidate2(dis(gen), dis(gen));
        Candidate candidate3(dis(gen), dis(gen));

        electoralDivisions.push_back(electoralDivision);

        candidates1.push_back(candidate1);
        candidates2.push_back(candidate2);
        candidates3.push_back(candidate3);
    }

    Leader leader1(dis(gen), dis(gen));
    CampaignTeam campaignTeam1(dis(gen));
    // PoliticalParty politicalPart1("Communist Party", leader1, candidates1, campaignTeam1);

    Leader leader2(dis(gen), dis(gen));
    CampaignTeam campaignTeam2(dis(gen));
    // PoliticalParty politicalPart2("Democratic Party", leader2, candidates2, campaignTeam2);

    Leader leader3(dis(gen), dis(gen));
    CampaignTeam campaignTeam3(dis(gen));
    // PoliticalParty politicalPart3("Republican Party", leader3, candidates3, campaignTeam3);

    PoliticalParty* politicalPart1 = new PoliticalParty("Communist Party", leader1, candidates1, campaignTeam1);
    PoliticalParty* politicalPart2 = new PoliticalParty("Democratic Party", leader2, candidates2, campaignTeam2);
    PoliticalParty* politicalPart3 = new PoliticalParty("Republican Party", leader3, candidates3, campaignTeam3);


    politicalParties.push_back(politicalPart1);
    politicalParties.push_back(politicalPart2);
    politicalParties.push_back(politicalPart3);


    for (const PoliticalParty* party : politicalParties) {
        cout << "Political party name: " << party->name << endl;
        cout << "Leader: popularity: " << party->leader.popularity << ", reputation: " << party->leader.reputation << endl;
        cout << "Candidate:" << endl;
        for (const Candidate& candidate : party->candidates) {
            cout << "   Popularity: " << candidate.popularity << ", skill: " << candidate.skill << endl;
        }
        cout << "Campaign team: efficiency: " << party->campaignTeam.efficiency << endl;
        cout << "Stances:" << endl;
        for (const Issue& issue : party->candidates[0].stances) {
            cout << "   Issue: " << issue.name << ", Significance: " << issue.significance << ", Approach: " << issue.approach << endl;
        }
        cout << endl;
    }

    for (const ElectoralDivision& division : electoralDivisions) {
        cout << "Division number: " << division.number << endl;
        for (const Issue& issue : division.stances) {
            cout << "   Issue: " << issue.name << ", Significance: " << issue.significance << ", Approach: " << issue.approach << endl;
        }
        cout << endl;
    }

    for (int i = 0; i < m; i++) {
        for (ElectoralDivision& division : electoralDivisions) {
            uniform_int_distribution<> disChance(0, 1);

            int Chance = disChance(gen);

            if (Chance == 1) {
                uniform_int_distribution<> disEvent(1, 4);

                int eventChance = disEvent(gen);

                cout << "Day " << i + 1 << ", division " << division.number << ":" << endl;

                if (eventChance == 1) {
                    DebateEvent debate;

                    debate.event(politicalPart1, politicalPart2, politicalPart3, division);
                    cout << politicalPart1->candidates[division.number - 1].popularity << endl;
                    cout << politicalPart2->candidates[division.number - 1].popularity << endl;
                    cout << politicalPart3->candidates[division.number - 1].popularity << endl;

                    cout << endl;
                } else if (eventChance == 2) {
                    int smallEventChance = disChance(gen);

                    if (smallEventChance == 0) {
                        PublicSpeakingEvent publicSpeaking;

                        publicSpeaking.event(politicalPart1, politicalPart2, politicalPart3, division);
                        cout << politicalPart1->candidates[division.number - 1].popularity << endl;
                        cout << politicalPart2->candidates[division.number - 1].popularity << endl;
                        cout << politicalPart3->candidates[division.number - 1].popularity << endl;
                    } else {
                        CommunityServiceEvent communityService;

                        communityService.event(politicalPart1, politicalPart2, politicalPart3, division);
                        cout << politicalPart1->candidates[division.number - 1].popularity << endl;
                        cout << politicalPart2->candidates[division.number - 1].popularity << endl;
                        cout << politicalPart3->candidates[division.number - 1].popularity << endl;
                    }

                    cout << endl;
                } else if (eventChance == 3) {
                    int smallEventChance = disChance(gen);

                    if (smallEventChance == 0) {
                        PolicyAnnouncementEvent policyAnnouncement;

                        policyAnnouncement.event(politicalPart1, politicalPart2, politicalPart3);
                    } else {
                        PressConferenceEvent pressConference;

                        pressConference.event(politicalPart1, politicalPart2, politicalPart3);
                    }

                    cout << endl;
                } else {
                    int smallEventChance = disChance(gen);
                    
                    if (smallEventChance == 0) {
                        ProtestEvent protestEvent;

                        protestEvent.event(division);
                    } else {
                        NewsReportEvent newsReportEvent;

                        newsReportEvent.event(division);
                    }

                    cout << endl;
                }
            } else {
                cout << "Day " << i + 1 << ", division " << division.number << ": No event." << endl << "\n";
            }
        }
    }

    for (const PoliticalParty* party : politicalParties) {
        cout << "Political party name: " << party->name << endl;
        cout << "Leader: popularity: " << party->leader.popularity << endl;
        cout << "Candidate:" << endl;
        for (const Candidate& candidate : party->candidates) {
            cout << "   Popularity: " << candidate.popularity << endl;
        }
    }

    cout << "Political party name: " << politicalPart1->name << endl;
    cout << "Leader: popularity: " << politicalPart1->leader.popularity << endl;
    cout << "Candidate:" << endl;
    for (const Candidate& candidate : politicalPart1->candidates) {
        cout << "   Popularity: " << candidate.popularity << endl;
    }

    cout << "Political party name: " << politicalPart2->name << endl;
    cout << "Leader: popularity: " << politicalPart2->leader.popularity << endl;
    cout << "Candidate:" << endl;
    for (const Candidate& candidate : politicalPart2->candidates) {
        cout << "   Popularity: " << candidate.popularity << endl;
    }

    cout << "Political party name: " << politicalPart3->name << endl;
    cout << "Leader: popularity: " << politicalPart3->leader.popularity << endl;
    cout << "Candidate:" << endl;
    for (const Candidate& candidate : politicalPart3->candidates) {
        cout << "   Popularity: " << candidate.popularity << endl;
    }

    for (const ElectoralDivision& division : electoralDivisions) {
        cout << "Division number: " << division.number << endl;
        for (const Issue& issue : division.stances) {
            cout << "   Issue: " << issue.name << ", Significance: " << issue.significance << ", Approach: " << issue.approach << endl;
        }
        cout << endl;
    }

}
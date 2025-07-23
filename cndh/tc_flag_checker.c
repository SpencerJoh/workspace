
bool check_telecommand_flags_inactive(const Telecommand_flag_CubeSpace_t* flags) {
    // CM 플래그들 체크
    if (flags->CM_TC_1 || flags->CM_TC_3 || flags->CM_TC_4 || 
        flags->CM_TC_5 || flags->CM_TC_6 || flags->CM_TC_60 || 
        flags->CM_TC_63 || flags->CM_TC_66) {
        printf("Warning: CM telecommand flags are active!\n");
        return false;
    }
    
    // CW1 플래그들 체크
    if (flags->CW1_TC_1 || flags->CW1_TC_3 || flags->CW1_TC_4 || 
        flags->CW1_TC_5 || flags->CW1_TC_6 || flags->CW1_TC_60 || 
        flags->CW1_TC_62 || flags->CW1_TC_64) {
        printf("Warning: CW1 telecommand flags are active!\n");
        return false;
    }
    
    // CW2 플래그들 체크
    if (flags->CW2_TC_1 || flags->CW2_TC_3 || flags->CW2_TC_4 || 
        flags->CW2_TC_5 || flags->CW2_TC_6 || flags->CW2_TC_60 || 
        flags->CW2_TC_62 || flags->CW2_TC_64) {
        printf("Warning: CW2 telecommand flags are active!\n");
        return false;
    }
    
    return true; // 모든 플래그가 비활성화됨
}



// 사용 예제
int main() {
    Telecommand_flag_CubeSpace_t tc_flags = {0}; // 모든 플래그를 0으로 초기화
    
    printf("Structure size: %zu bytes\n", sizeof(Telecommand_flag_CubeSpace_t));
    printf("(Original bool version would be: %zu bytes)\n", sizeof(bool) * 24);
    printf("\n");
    
    // 테스트용으로 몇 개 플래그 설정 (아주 간단!)
    tc_flags.CM_TC_1 = 1;      // 활성화
    tc_flags.CM_TC_66 = 1;     // 활성화
    tc_flags.CW1_TC_60 = 1;    // 활성화
    tc_flags.CW2_TC_3 = 1;     // 활성화
    
    // 주기적 체크 시뮬레이션
    for (int i = 0; i < 4; i++) {
        periodic_telecommand_flag_check(&tc_flags);
        
        // 각 스텝마다 일부 플래그 변경
        if (i == 0) {
            printf("Turning off CM_TC_1...\n");
            tc_flags.CM_TC_1 = 0;
        } else if (i == 1) {
            printf("Resetting all CM flags...\n");
            reset_CM_flags(&tc_flags);
        } else if (i == 2) {
            printf("Resetting all flags...\n");
            reset_all_telecommand_flags(&tc_flags);
        }
    }
    
    return 0;
}

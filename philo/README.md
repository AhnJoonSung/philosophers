## Overview

이 과제를 성공적으로 수행하려면 다음 사항을 알아야 합니다:
• 하나 이상의 철학자들이 둥근 테이블에 앉아 있습니다.
테이블 가운데에는 스파게티가 가득 담긴 큰 그릇이 있습니다.
• 철학자들은 번갈아가며 먹고, 생각하거나 잠을 잡니다.
한번에 하나의 행동만 할 수 있습니다.
• 테이블 위에는 철학자 수만큼 포크가 있습니다.
• 철학자는 먹을 때 오른손과 왼손에 각각 포크를 들고 먹습니다.
• 철학자가 식사를 마치면 포크를 테이블에 돌려놓고 잠을 잡니다.
깨어나면 다시 생각을 시작합니다.
철학자가 굶주려 죽으면 시뮬레이션이 중단됩니다.

• 모든 철학자는 먹어야 하며, 절대 굶주리면 안 됩니다.

___

## Global rules

- 전역 변수 금지
- 다음 인자들을 받아야 합니다:
  - number_of_philosophers: 철학자의 수이자 포크의 수
  - time_to_die, 밀리초 단위: 만약 철학자가 마지막 식사 시작 이후 또는 시뮬레이션 시작 이후 time_to_die 밀리초 동안 식사를 시작하지 않으면, 그들은 죽습니다.
  - time_to_eat, 밀리초 단위: 철학자가 먹는 데 걸리는 시간. 이 시간 동안 그들은 두 개의 포크를 잡고 있어야 합니다.
  - time_to_sleep, 밀리초 단위: 철학자가 잠을 자는 시간
  - number_of_must_eat, 선택적 인자: 모든 철학자가 최소한 n번 식사를 했다면, 시뮬레이션은 중단됩니다. 지정되지 않은 경우, 철학자가 죽었을 때 시뮬레이션이 중단됩니다.
- 각 철학자는 1부터 철학자의 수까지 번호를 가집니다.
- 철학자 번호 1번부터 순서대로 앉습니다. (1은 N옆에)

프로그램의 로그에 대해서:
- 철학자의 상태 변경은 다음과 같이 형식화되어야 합니다:
  - timestamp_in_ms X has taken a fork
  - timestamp_in_ms X is eating
  - timestamp_in_ms X is sleeping
  - timestamp_in_ms X is thinking
  - timestamp_in_ms X died
  밀리초 단위의 현재 타임스탬프로 timestamp_in_ms를 대체하고, X는 철학자 번호로 대체하세요.
- 표시된 상태 메시지는 다른 메시지와 섞이지 않아야 합니다.
- 철학자의 죽음을 알리는 메시지는 철학자가 실제로 죽은 후 10밀리초 이내에 표시되어야 합니다.
- 다시 한번, 철학자들은 죽지 않도록 해야 합니다!

---

## Mandatory

프로그램 이름: philo

제출 파일: Makefile, *.h, *.c, philo/ 디렉토리 안에

Makefile: NAME, all, clean, fclean, re
인자: 철학자의 수, 죽는 시간, 먹는 시간, 잠자는 시간, [각 철학자가 먹어야 하는 횟수]

외부 함수: memset, printf, malloc, free, write, usleep, gettimeofday, pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock

Libft 허용 여부: 아니오

설명: 스레드와 뮤텍스를 사용하는 철학자들

필수 부분에 대한 특정 규칙은 다음과 같습니다:

각 철학자는 하나의 스레드여야 합니다.
철학자 한 쌍 사이에는 하나의 포크가 있습니다. 따라서, 여러 명의 철학자가 있다면, 각 철학자는 왼쪽에 하나, 오른쪽에 하나, 두 개의 포크를 가집니다. 철학자가 한 명뿐인 경우, 테이블 위에는 포크가 하나만 있어야 합니다.
철학자들이 포크를 복제하지 않도록 하기 위해, 각 포크의 상태를 보호하기 위한 뮤텍스를 사용해야 합니다.

---

## Bonus

프로그램 이름: philo_bonus

제출 파일: Makefile, *.h, *.c, philo_bonus/ 디렉토리 안에

Makefile: NAME, all, clean, fclean, re

인자: 철학자의 수, 죽는 시간, 먹는 시간, 잠자는 시간, [각 철학자가 먹어야 하는 횟수]

외부 함수: memset, printf, malloc, free, write, fork, kill, exit, pthread_create, pthread_detach, pthread_join, usleep, gettimeofday, waitpid, sem_open, sem_close, sem_post, sem_wait, sem_unlink

Libft 허용 여부: 아니오

설명: 프로세스와 세마포어를 사용하는 철학자들

보너스 부분의 프로그램은 필수 프로그램과 동일한 인자를 받습니다. 전체 규칙 챕터의 요구 사항을 준수해야 합니다.
보너스 부분에 대한 특정 규칙은 다음과 같습니다:
- 모든 포크는 테이블 중앙에 놓입니다.
- 포크의 상태는 메모리에 있지 않지만, 사용 가능한 포크의 수는 세마포어로 표현됩니다.
- 각 철학자는 하나의 프로세스여야 합니다. 하지만 메인 프로세스는 철학자가 되어서는 안 됩니다.

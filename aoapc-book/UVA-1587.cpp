#include <cstdio>
#include <utility>
#include <map>

int main()
{
    while(true)
    {
        int x, y;

        std::map<int, int> edge;
        std::map<std::pair<int,int>, int> plan;
        bool has_square = false;

        for (int i = 0; i < 6; i++)
        {
            int eof = scanf("%d %d", &x, &y);
            if (eof == EOF) return 0;

            if (x > y)
            {
                std::swap(x, y);
            }
            else if (x == y)
            {
                has_square = true;
            }

            edge[x]++;
            edge[y]++;
            plan[{x,y}]++;
        }

        int edge_kind = edge.size();
        int plan_kind = plan.size();

        switch (edge_kind)
        {
        case 1:
            goto box;
        case 2:
            if (plan_kind != 2) break;
            if (x == y && plan[{x,y}] == 2)
            {
                goto box;
            }
            else if (x != y && plan[{x,y}] == 4)
            {
                goto box;
            }
            break;
        case 3:
            if (plan_kind != 3) break;
            if (has_square) break;
            if (edge[x] == 4 && edge[y] == 4) goto box;
            break;
        default:
            break;
        }

no_box:
        printf("IMPOSSIBLE\n");   
        continue;
box:
        printf("POSSIBLE\n");

    }

    return 0;
}
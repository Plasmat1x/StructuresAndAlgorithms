#ifndef ALGORITHMS_H
#define ALGORITHMS_H

namespace algo
{
    namespace add
    {
        /// <summary>
        /// if 'a' more 'b' return true
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <returns></returns>
        template<typename T>
        inline bool ascending(T a, T b)
        {
            return a > b;
        }

        /// <summary>
        /// if 'a' less 'b' return true
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <returns></returns>
        template<typename T>
        inline bool descending(T a, T b)
        {
            return a < b;
        }

        /// <summary>
        /// set min or max element on [0] index
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="arr"></param>
        /// <param name="size"></param>
        /// <param name="comparsion"></param>
        template<typename T>
        void set(T arr[], size_t size, bool (*comparsion)(T, T))
        {
            T tmp = arr[0];
            int i = 0;
            for (i = 1; i < size; i++)
            {
                if (comparsion(tmp, arr[i])) tmp = arr[i];
            }
            arr[0] = tmp;
        }
    }//---end add namespace---

    namespace sort
    {
        template<typename T>
        void bubble(T arr[], size_t size, bool (*comparsion)(T, T))
        {
            for (int i = 0; i < size - 1; i++)
            {
                for (int j = 0; j < size - i - 1; j++)
                {
                    if (comparsion(arr[j], arr[j + 1]))
                    {
                        T tmp = arr[j];
                        arr[j] = arr[j + 1];
                        arr[j + 1] = tmp;
                    }
                }
            }
        }

        template<typename T>
        void quick(T arr[], size_t size, bool (*comparsion)(T, T))
        {
            int i = 0;
            int j = size - 1;
            T p = arr[size / 2]; //pivot point 
            T tmp = 0;

            do
            {
                while (comparsion(p, arr[i]))
                    i++;
                while (comparsion(arr[j], p))
                    j--;

                if (i <= j)
                {
                    tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                    i++;
                    j--;
                }
            } while (i <= j);

            if (j > 0) quick(arr, j + 1, *comparsion);
            if (i < size) quick(arr + i, size - i, *comparsion);
        }

        template<typename T>
        void select(T arr[], size_t size, bool (*comparsion)(T, T))
        {
            for (int i = 0; i < size; i++) //i - start index
            {
                int b = i;   // b - best index
                for (int j = i + 1; j < size; j++) // j - curent index
                {
                    if (comparsion(arr[b], arr[j]))
                        b = j;
                }

                T tmp = arr[i];
                arr[i] = arr[b];
                arr[b] = tmp;
            }
        }

        template<typename T>
        void insert(T arr[], size_t size, bool (*comparsion)(T, T))
        {
            T b = arr[0];
            T tmp = 0;
            int i = 0;
            int j = 0;

            add::set(arr, size, *comparsion);

            for (i = 1; i < size; i++)
            {
                tmp = arr[i];
                for (j = i - 1; comparsion(arr[j], tmp); j--)
                {
                    arr[j+1] = arr[j];
                }
                arr[j + 1] = tmp;
            }

            for (j = 1; j < size && comparsion(b, arr[j]); j++)
            {
                arr[j - 1] = arr[j];
            }
            arr[j - 1] = b;
        }

        template <typename T>
        void shell(T arr[], size_t size, bool (*comparsion)(T, T))
        {
            int i = 0;
            int j = 0;
            int step = 0;
            T tmp = 0;
            for (step = size / 2; step > 0; step /= 2)
            {
                for (i = step; i < size; i++)
                {
                    for (j = i - step; j >= 0 && comparsion(arr[j], arr[j + step]); j -= step)
                    {
                        tmp = arr[j];
                        arr[j] = arr[j + step];
                        arr[j + step] = tmp;
                    }
                }
            }
        }

        template<typename T>
        void shaker(T arr[], size_t size, bool (*comparsion)(T, T))
        {
            int l = 0;
            int r = size - 1;
            int flag = 1;
            T t = 0;

            while ((l < r) && flag > 0)
            {
                flag = 0;
                for (int i = l; i < r; i++)
                {
                    if (comparsion(arr[i], arr[i + 1]))
                    {
                        t = arr[i];
                        arr[i] = arr[i + 1];
                        arr[i + 1] = t;
                        flag = 1;
                    }
                }
                r--;
                for (int i = r; i > l; i--)
                {
                    if (comparsion(arr[i - 1], arr[i]))
                    {
                        t = arr[i];
                        arr[i] = arr[i - 1];
                        arr[i - 1] = t;
                        flag = 1;
                    }
                }
                l++;
            }
        }
        
    }//---end sort namespace---

    namespace search
    {
        /// <summary>
        /// included shell sort
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="arr"></param>
        /// <param name="size"></param>
        /// <param name="search"></param>
        /// <param name="comparsion"></param>
        /// <returns></returns>
        template<typename T>
        int binary_shell(T arr[], size_t size, T search, bool (*comparsion)(T, T))
        {
            int p = 0;
            int l = 0;
            int r = size;

            sort::shell(arr, size, *comparsion);

            while (true)
            {
                p = (l + r) / 2;

                if (comparsion(arr[p], search))
                {
                    r = p - 1;
                }
                else if(comparsion(search, arr[p]))
                {
                    l = p + 1;
                }
                else
                {
                    return p;
                }
                if (l > r)
                {
                    return -1;
                }
            }
            return -1;
        }

        /// <summary>
        /// without sorting, use sorting before
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="arr"></param>
        /// <param name="size"></param>
        /// <param name="search"></param>
        /// <param name="comparsion"></param>
        /// <returns></returns>
        template<typename T>
        int binary(T arr[], size_t size, T search, bool (*comparsion)(T, T))
        {
            int p = 0;
            int l = 0;
            int r = size;

            while (true)
            {
                p = (l + r) / 2;

                if (comparsion(arr[p], search))
                {
                    r = p - 1;
                }
                else if (comparsion(search, arr[p]))
                {
                    l = p + 1;
                }
                else
                {
                    return p;
                }
                if (l > r)
                {
                    return -1;
                }
            }
            return -1;
        }
    }//---end search namespace---

}//---end algo namespace---

#endif // !ALGORITHMS_H


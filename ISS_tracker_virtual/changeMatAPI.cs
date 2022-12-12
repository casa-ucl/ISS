using System.Collections;
using UnityEngine;
using UnityEngine.Networking;

public class changeMatAPI : MonoBehaviour
{
    public string wwwRequest = "https://api.wheretheiss.at/v1/satellites/25544"; // The endpoint of the API
    public Material[] dot_mat;//Array of materials (to be added from the inspector)
    public GameObject[] cubes; //Array of the GameObjects

    public GameObject map;

    public Color colorOff = new Color();
    public Color colorOn = new Color();
    public double latValue=0f;
    public double longValue=0f;

    // Start is called before the first frame update
    void Start()
    {
        StartCoroutine(apiCall()); //When the App Start, Start the CoRoutine IEnumerator matChange()
    }

    IEnumerator apiCall(){

        
        UnityWebRequest www = UnityWebRequest.Get(wwwRequest); //Send the request to the API endpoint

        yield return www.SendWebRequest(); //Wait for the response
        Debug.Log(www.downloadHandler.text);
        
        var response = JsonUtility.FromJson<issTracker.Root>(www.downloadHandler.text); //parse the resonse as the public class issTracker

        Debug.Log(response.latitude); //Show the latitude in the console
        
        StartCoroutine(matChange(response));
        StartCoroutine(rotationMap(response));
        
        yield return new WaitForSeconds(5); //Wait 5 second
        StartCoroutine(apiCall()); 
        
    }

IEnumerator rotationMap(issTracker.Root response){
while(true){

    longValue = response.longitude; //Comment this line to test dummy data

    float step=1.5f*Time.deltaTime;
    
    Vector3 rotation=new Vector3(map.transform.localEulerAngles.x,-(float)longValue,map.transform.localEulerAngles.z);
    
    map.transform.localRotation= Quaternion.Lerp(map.transform.localRotation,Quaternion.Euler(rotation),step);

    yield return null;
}
}

    IEnumerator matChange(issTracker.Root response)
    {
        

    latValue=response.latitude; //comment this line to test the function with dummy value from the inspector

        //67.5 > 
        //45 - 67.5
        //22.5 - 45
        //0 - 22.5
        //-22.5 - 0
        //-45 - -22.5
        //-67.5 - -45
        //< -67.5
        if ( latValue >= 67.5f) //if the latitude is < 20f change the color of the mat 0 to ON and all the other to OFF 
        {
            dot_mat[0].color = colorOn;
            
            cubes[0].GetComponent<MeshRenderer>().enabled=true;
            //cubes[0].GetComponent<Transform>().position=new Vector3(cubes[0].GetComponent<Transform>().position.x,1,cubes[0].GetComponent<Transform>().position.z);
            

            for (int i = 0; i < dot_mat.Length; i++)
            {
                if (i == 0)
                {
                    continue;
                }
                dot_mat[i].color = colorOff;
                cubes[i].GetComponent<MeshRenderer>().enabled=false;
            }

        }
        else if (latValue >= 45f && latValue < 67.5f) //if the latitude is between < 21f and 40, change the color of the mat 1 to ON and all the other to OFF
        {
            dot_mat[1].color = colorOn;
            cubes[1].GetComponent<MeshRenderer>().enabled=true;
            for (int i = 0; i < dot_mat.Length; i++)
            {
                if (i == 1)
                {
                    continue;
                }
                dot_mat[i].color = colorOff;
                cubes[i].GetComponent<MeshRenderer>().enabled=false;
            }
        }
        else if (latValue >= 22.5f && latValue < 45f)
        {
            dot_mat[2].color = colorOn;
            cubes[2].GetComponent<MeshRenderer>().enabled=true;
            for (int i = 0; i < dot_mat.Length; i++)
            {
                if (i == 2)
                {
                    continue;
                }
                dot_mat[i].color = colorOff;
                cubes[i].GetComponent<MeshRenderer>().enabled=false;
            }
        }
        else if (latValue >= 0f && latValue < 22.5f)
        {
            dot_mat[3].color = colorOn;
            cubes[3].GetComponent<MeshRenderer>().enabled=true;
            for (int i = 0; i < dot_mat.Length; i++)
            {
                if (i == 3)
                {
                    continue;
                }
                dot_mat[i].color = colorOff;
                cubes[i].GetComponent<MeshRenderer>().enabled=false;
            }
        }
        else if (latValue >= -22.5f && latValue < 0f)
        {
            dot_mat[4].color = colorOn;
            cubes[4].GetComponent<MeshRenderer>().enabled=true;
            for (int i = 0; i < dot_mat.Length; i++)
            {
                if (i == 4)
                {
                    continue;
                }
                dot_mat[i].color = colorOff;
                cubes[i].GetComponent<MeshRenderer>().enabled=false;
            }
        }
        else if (latValue >= -45f && latValue < -22.5f)
        {
            dot_mat[5].color = colorOn;
            cubes[5].GetComponent<MeshRenderer>().enabled=true;
            for (int i = 0; i < dot_mat.Length; i++)
            {
                if (i == 5)
                {
                    continue;
                }
                dot_mat[i].color = colorOff;
                cubes[i].GetComponent<MeshRenderer>().enabled=false;
            }
        }
        else if (latValue >= -67.5f && latValue < -45f)
        {
            dot_mat[6].color = colorOn;
            cubes[6].GetComponent<MeshRenderer>().enabled=true;
            for (int i = 0; i < dot_mat.Length; i++)
            {
                if (i == 6)
                {
                    continue;
                }
                dot_mat[i].color = colorOff;
                cubes[i].GetComponent<MeshRenderer>().enabled=false;
            }
        }
        else if (latValue < -67.5f ) //if the latitude is > 101f change the color of the mat 5 to ON and all the other to OFF
        {
            dot_mat[7].color = colorOn;
            cubes[7].GetComponent<MeshRenderer>().enabled=true;
            for (int i = 0; i < dot_mat.Length; i++)
            {
                if (i == 7)
                {
                    continue;
                }
                dot_mat[i].color = colorOff;
                cubes[i].GetComponent<MeshRenderer>().enabled=false;
        }


    }
             yield return null;
}


//CLass used to parse the JSON
public class issTracker
{
    [System.Serializable]
    public class Root
    {
        public string name;
        public int id;
          public double latitude;
        public double longitude;
        public double altitude;
        public double velocity;
        public string visibility;
        public double footprint;
        public int timestamp;
        public double daynum;
        public double solar_lat;
        public double solar_lon;
        public string units;
    }
}
}